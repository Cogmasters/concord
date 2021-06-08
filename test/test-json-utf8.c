#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <locale.h>

#include "discord.h"

#include "orka-utils.h"
#include "json-actor.c"

#define A "Íñdîæ"
#define B "m\\u00fcller"
#define C "的"
#define D "😊"
#define UTF8_JSON "{\"a\":\""A"\",\"b\":\""B"\",\"c\":\""C"\",\"d\":\""D"\"}"

#define DISCORD_JSON "{\"audit_log_entries\": [{\"id\": \"846844331545722920\", \"user_id\": \"140931563499159552\", \"target_id\": null, \"action_type\": 40, \"changes\": [{\"key\": \"code\", \"new_value\": \"qGFG7TPS\"}, {\"key\": \"channel_id\", \"new_value\": \"176404078702624768\"}, {\"key\": \"inviter_id\", \"new_value\": \"140931563499159552\"}, {\"key\": \"uses\", \"new_value\": 0}, {\"key\": \"max_uses\", \"new_value\": 0}, {\"key\": \"max_age\", \"new_value\": 604800}, {\"key\": \"temporary\", \"new_value\": false}]}], \"users\": [{\"id\": \"140931563499159552\", \"username\": \"m\\u00fcller\", \"avatar\": \"ce7e4481794708a0a5acb1e14f468b01\", \"discriminator\": \"5436\", \"public_flags\": 128}], \"integrations\": [], \"webhooks\": []}"

int main()
{
  setlocale(LC_ALL, "");

  char a[16], b[16], c[16], d[16];
  char payload[4096];

  json_extract(UTF8_JSON, sizeof(UTF8_JSON), \
      "(a):s,(b):s,(c):s,(d):s", a, b, c, d);
  printf("original a: "A"\tnew a: %s\n", a);
  printf("original b: "B"\tnew b: %s\n", b);
  printf("original c: "C"\tnew c: %s\n", c);
  printf("original d: "D"\tnew d: %s\n", d);

  json_inject(payload, sizeof(payload), \
      "(a):s,(b):s,(c):s,(d):s", a, b, c, d);
  printf("original json:\n"UTF8_JSON"\nnew json:\n%s\n", payload);

  struct discord_audit_log *audit_log = discord_audit_log_alloc();
  discord_audit_log_from_json(DISCORD_JSON, sizeof(DISCORD_JSON), audit_log);
  discord_audit_log_to_json(payload, sizeof(payload), audit_log);
  printf("original json:\n"DISCORD_JSON"\nnew json:\n%s\n", payload);

  discord_audit_log_free(audit_log);

  return EXIT_SUCCESS;
}

