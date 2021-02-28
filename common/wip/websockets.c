#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "curl-websocket.h"

#include "websockets.h"
#include "orka-utils.h"


/* init easy handle with some default opt */
static CURL*
custom_cws_new(dati *ws)
{
  //missing on_binary, on_ping, on_pong
  struct cws_callbacks cws_cbs;
  memset(&cws_cbs, 0, sizeof(cws_cbs));
  cws_cbs.on_connect = &ws_on_connect_cb;
  cws_cbs.on_text = &ws_on_text_cb;
  cws_cbs.on_close = &ws_on_close_cb;
  cws_cbs.data = ws;

  CURL *new_ehandle = cws_new(ws->base_url, NULL, &cws_cbs);
  ASSERT_S(NULL != new_ehandle, "Out of memory");

  CURLcode ecode;
  //enable follow redirections
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_FOLLOWLOCATION, 2L);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  /* DEBUG MODE SETOPTS START */

  //set debug callback
  D_ONLY(ecode = curl_easy_setopt(new_ehandle, CURLOPT_DEBUGFUNCTION, &curl_debug_cb));
  D_ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set ptr to settings containing dump files
  D_ONLY(ecode = curl_easy_setopt(new_ehandle, CURLOPT_DEBUGDATA, &ws->p_client->settings));
  D_ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //enable verbose
  D_ONLY(ecode = curl_easy_setopt(new_ehandle, CURLOPT_VERBOSE, 1L));
  D_ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  /* DEBUG MODE SETOPTS END */

/* @todo
  // execute user-defined curl_easy_setopts
  if (ws->setopt_cb) {
    (*ws->setopt_cb)(new_ehandle, ws->cbs.data);
  }
*/

  return new_ehandle;
}

void
ws_init(struct websockets_s *ws, char base_url[])
{
  ws->status = WS_DISCONNECTED;
  ws->reconnect.threshold = 5; //hard coded @todo make configurable

  ws->ehandle = custom_cws_new(ws);
  ws->mhandle = curl_multi_init();
  ws->base_url = base_url;
}

void
ws_cleanup(struct websockets_s *ws)
{
  curl_multi_cleanup(ws->mhandle);
  cws_free(ws->ehandle);
}

static void
event_loop(struct websockets_s *ws)
{
  curl_multi_add_handle(ws->mhandle, ws->ehandle);

  if ( !(*ws->cbs.on_start)(ws->cbs.data) ) {
    return; /* EARLY RETURN */

  // kickstart a connection then enter loop
  CURLMcode mcode;
  int is_running = 0;
  mcode = curl_multi_perform(ws->mhandle, &is_running);
  ASSERT_S(CURLM_OK == mcode, curl_multi_strerror(mcode));

  do {
    int numfds;

    ws->now_tstamp = orka_timestamp_ms(); // updates our concept of 'now'

    mcode = curl_multi_perform(ws->mhandle, &is_running);
    ASSERT_S(CURLM_OK == mcode, curl_multi_strerror(mcode));

    //wait for activity or timeout @todo make wait_ms configurable
    mcode = curl_multi_wait(ws->mhandle, NULL, 0, 1000, &numfds);
    ASSERT_S(CURLM_OK == mcode, curl_multi_strerror(mcode));

    if (ws->status != WS_CONNECTED) continue; // wait until connection is established

    (*ws->on_idle)(ws->cbs.data);

  } while(is_running);

  curl_multi_remove_handle(ws->mhandle, ws->ehandle);
}

static enum ws_status
attempt_reconnect(struct websockets_s *ws)
{
  switch (ws->status) {
  default:
      if (ws->reconnect.count < ws->reconnect.threshold)
        break;

      PRINT("Failed all reconnect attempts (%d)", ws->reconnect.count);
      ws->status = WS_DISCONNECTED;
  /* fall through */
  case WS_DISCONNECTED:
      return ws->status; /* is WS_DISCONNECTED */
  }

  /* force reset */
  cws_free(ws->ehandle);
  ws->ehandle = custom_cws_new(ws);

  ++ws->reconnect.count;

  return ws->status; /* is different than WS_DISCONNECTED */
}

/* connects to the websockets server */
void
ws_run(struct websockets_s *ws)
{
  ASSERT_S(WS_DISCONNECTED == ws->status, 
      "Failed attempt to run websockets recursively");

  while (1) {
    event_loop(ws);
    if (attempt_reconnect(ws) == WS_DISCONNECTED) {
      break;
    }
  }
}
