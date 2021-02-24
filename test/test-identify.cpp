#include "discord-common.h"
#include "json-actor.h"

namespace  iden = discord::websockets::identify;

int main (int argc, char ** argv)
{

  iden::dati data;
  iden::dati_init(&data);
  char payload[1024];
  data.token = "this is a long token";
  int ret = json_inject(payload, sizeof(payload),
                        "(op):2" // IDENTIFY OPCODE
                        "(d):F",
                        &iden::dati_to_json, &data);
  fprintf(stderr, "%.*s\n", ret, payload);
  iden::dati_cleanup(&data);
}



