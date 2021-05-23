#include <logconf.h>

int main(int argc, char *argv[])
{
  const char *file;
  if (argc > 1)
    file = argv[1];
  else
    file = "../bots/bot.config";

  char *varA = "Hello"; 
  int varB = 1337;
  struct { int x } varC = { .x = 707 };

  struct logconf conf={};

  // initialize and link conf to a .config file
  logconf_setup(&conf, file);

  // assign tags to variable unique mem address
  logconf_add_id(&conf, &varA, "INT A");
  logconf_add_id(&conf, &varB, "CHAR B");
  logconf_add_id(&conf, &varC, "STRUCT C");

  // get some JSON field written in .config file
  struct sized_buffer level = logconf_get_field(&conf, "logging.level");
  // print the field
  log_trace("Logging level: %.*s", (int)level.size, level.start);

  // print the tag by referencing to the variable unique address
  log_trace("char varA tag: %s", logconf_tag(&conf, &varA));
  log_trace("char varB tag: %s", logconf_tag(&conf, &varC));
  log_trace("char varC tag: %s", logconf_tag(&conf, &varB));

  // print to 'logging.filename' (@todo better function name?)
  log_http(
    &conf, 
    &varA, 
    "TITLE1", 
    (struct sized_buffer){"BODY1", 5},
    "%s", varA);

  log_http(
    &conf, 
    &varB, 
    "TITLE2", 
    (struct sized_buffer){"BODY2", 5},
    "%d", varB);

  log_http(
    &conf, 
    &varC, 
    "TITLE3", 
    (struct sized_buffer){"BODY3", 5},
    "%d", varC.x);

  // cleanup conf resources
  logconf_cleanup(&conf);
}
