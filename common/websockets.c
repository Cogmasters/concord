#include <stdio.h>
#include <stdlib.h>

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

  /* DEBUG ONLY FUNCTIONS */
  //set debug callback
  D_ONLY(ecode = curl_easy_setopt(new_ehandle, CURLOPT_DEBUGFUNCTION, &curl_debug_cb));
  D_ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set ptr to settings containing dump files
  D_ONLY(ecode = curl_easy_setopt(new_ehandle, CURLOPT_DEBUGDATA, &ws->p_client->settings));
  D_ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //enable verbose
  D_ONLY(ecode = curl_easy_setopt(new_ehandle, CURLOPT_VERBOSE, 1L));
  D_ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
  /* * * * * * * * * * * */

  return new_ehandle;
}

void
ws_init(struct websockets_s *ws, char base_url[])
{
  ws->status = WS_DISCONNECTED;

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
  /* @todo callback1 * *

  //get session info before starting it
  get_bot(ws->p_client, &ws->session);

  VASSERT_S(ws->session.remaining != 0, 
      "Reach session starts threshold (%d)\n\t"
      "Please wait %d seconds and try again", 
      ws->session.total, ws->session.reset_after/1000);

  * * * * * * * * * * */

  int is_running = 0;

  curl_multi_perform(ws->mhandle, &is_running);

  CURLMcode mcode;
  do {
    int numfds;

    ws->now_tstamp = orka_timestamp_ms(); // updates our concept of 'now'

    mcode = curl_multi_perform(ws->mhandle, &is_running);
    ASSERT_S(CURLM_OK == mcode, curl_multi_strerror(mcode));

    //wait for activity or timeout
    mcode = curl_multi_wait(ws->mhandle, NULL, 0, 1000, &numfds);
    ASSERT_S(CURLM_OK == mcode, curl_multi_strerror(mcode));

    if (ws->status != WS_CONNECTED) continue; // wait until connection is established
    
    /* CONNECTION IS ESTABLISHED */

    /* @todo callback 2
    if (ws->hbeat.interval_ms < (ws->now_tstamp - ws->hbeat.tstamp)) {
      ws_send_heartbeat(ws);

      ws->hbeat.tstamp = ws->now_tstamp; //update heartbeat timestamp
    }

    if (ws->cbs.on_idle) {
      (*ws->cbs.on_idle)(ws->p_client, ws->me);
    }
    */

  } while(is_running);
}

/* connects to the websockets server */
void
ws_run(struct websockets_s *ws)
{
  ASSERT_S(WS_CONNECTED != ws->status, "Can't have recursive connections");

  do {
    curl_multi_add_handle(ws->mhandle, ws->ehandle);
    event_loop(ws);
    curl_multi_remove_handle(ws->mhandle, ws->ehandle);

    if (WS_DISCONNECTED == ws->status) break;
    if (ws->reconnect_attempts >= 5) break;

    // full shutdown of old connection before reconnecting
    cws_free(ws->ehandle);
    ws->ehandle = custom_cws_new(ws);

    ++ws->reconnect_attempts;
  } while (1);

  if (WS_DISCONNECTED != ws->status) {
    PRINT("Failed all reconnect attempts (%d)", ws->reconnect_attempts);
    ws->status = WS_DISCONNECTED;
  }
}
