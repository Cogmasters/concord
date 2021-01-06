#include <stdio.h>
#include <stdlib.h>

#include <libdiscord.h>
#include "discord-common.h"
#include "curl-websocket.h"

#define BASE_WEBSOCKETS_URL "wss://gateway.discord.gg/?v=6&encoding=json"

static void
_ws_on_connect_cb(void *data, CURL *ehandle, const char *ws_protocols)
{
  struct discord_ws_s *ws = data;
  (void)ws;

  D_PRINT("Connected, WS-Protocols: '%s'", ws_protocols);

  (void)ehandle;
  (void)ws_protocols;
}

static char*
_discord_payload_strevent(enum ws_opcode opcode)
{

//if case matches return token as string
#define CASE_RETURN_STR(opcode) case opcode: return #opcode

  switch(opcode) {
    CASE_RETURN_STR(GATEWAY_DISPATCH);
    CASE_RETURN_STR(GATEWAY_HEARTBEAT);
    CASE_RETURN_STR(GATEWAY_IDENTIFY);
    CASE_RETURN_STR(GATEWAY_PRESENCE_UPDATE);
    CASE_RETURN_STR(GATEWAY_VOICE_STATE_UPDATE);
    CASE_RETURN_STR(GATEWAY_RESUME);
    CASE_RETURN_STR(GATEWAY_RECONNECT);
    CASE_RETURN_STR(GATEWAY_REQUEST_GUILD_MEMBERS);
    CASE_RETURN_STR(GATEWAY_INVALID_SESSION);
    CASE_RETURN_STR(GATEWAY_HELLO);
    CASE_RETURN_STR(GATEWAY_HEARTBEAT_ACK);

  default:
    ERROR("Invalid ws opcode:\t%d", opcode);
  }
}


static void
_ws_on_text_cb(void *data, CURL *ehandle, const char *text, size_t len)
{
  struct discord_ws_s *ws = data;

  D_PRINT("ON_TEXT:\n\t\t%s", text);

  jscon_scanf((char*)text, "%s[t]", ws->payload.event_name);
  jscon_scanf((char*)text, "%d[s]", &ws->payload.seq_number);
  jscon_scanf((char*)text, "%d[op]", &ws->payload.opcode);
  jscon_scanf((char*)text, "%ji[d]", &ws->payload.event_data);

  D_NOTOP_PRINT("OP:\t\t%s\n\tEVENT_NAME:\t%s\n\tSEQ_NUMBER:\t%d", 
              _discord_payload_strevent(ws->payload.opcode), 
              !*ws->payload.event_name //if event name exists
                 ? "NULL" //print NULL
                 : ws->payload.event_name, //otherwise, event name
              ws->payload.seq_number);

  switch (ws->payload.opcode){
  case GATEWAY_HEARTBEAT_ACK:
      break; 
  default:
      ERROR("Unknown gateway opcode (code: %d)", ws->payload.opcode);
  }

  (void)len;
  (void)ehandle;
}

static void
_ws_on_close_cb(void *data, CURL *ehandle, enum cws_close_reason cwscode, const char *reason, size_t len)
{
    struct discord_ws_s *ws = data;
    (void)ws;

    D_PRINT("CLOSE=%4d %zd bytes '%s'", cwscode, len, reason);

    (void)ehandle;
    (void)cwscode;
    (void)len;
    (void)reason;
}


/* init easy handle with some default opt */
static CURL*
_discord_easy_init(struct discord_ws_s *ws)
{
  //missing on_binary, on_ping, on_pong
  struct cws_callbacks cws_cbs = {
    .on_connect = &_ws_on_connect_cb,
    .on_text = &_ws_on_text_cb,
    .on_close = &_ws_on_close_cb,
    .data = ws,
  };

  CURL *new_ehandle = cws_new(BASE_WEBSOCKETS_URL, NULL, &cws_cbs);
  ASSERT_S(NULL != new_ehandle, "Out of memory");

  CURLcode ecode;
  D_ONLY(ecode = curl_easy_setopt(new_ehandle, CURLOPT_VERBOSE, 2L));
  D_ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  ecode = curl_easy_setopt(new_ehandle, CURLOPT_FOLLOWLOCATION, 2L);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  return new_ehandle;
}

static CURLM*
_discord_multi_init()
{
  CURLM *new_mhandle = curl_multi_init();
  ASSERT_S(NULL != new_mhandle, "Out of memory");

  return new_mhandle;
}

void
Discord_ws_init(struct discord_ws_s *ws, char token[])
{
  ws->ehandle = _discord_easy_init(ws);
  ws->mhandle = _discord_multi_init();

  (void)token;
}

void
Discord_ws_cleanup(struct discord_ws_s *ws)
{
  curl_multi_cleanup(ws->mhandle);
  cws_free(ws->ehandle);
}

static void
_ws_main_loop(struct discord_ws_s *ws)
{
  int is_running = 0;

  curl_multi_add_handle(ws->mhandle, ws->ehandle);

  curl_multi_perform(ws->mhandle, &is_running);

  CURLMcode mcode;
  do {
    int numfds;

    mcode = curl_multi_perform(ws->mhandle, &is_running);
    ASSERT_S(CURLM_OK == mcode, curl_multi_strerror(mcode));
    
    //wait for activity or timeout
    mcode = curl_multi_poll(ws->mhandle, NULL, 0, 1000, &numfds);
    ASSERT_S(CURLM_OK == mcode, curl_multi_strerror(mcode));
  } while(is_running);

  curl_multi_remove_handle(ws->mhandle, ws->ehandle);
}

void
discord_connect(discord_t *discord)
{
  _ws_main_loop(&discord->ws);
}
