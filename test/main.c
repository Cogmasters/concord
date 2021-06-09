#include "greatest.h"
#include "orka-utils.h"
#include "ntl.h"

#include "suite-json.c"

SUITE_EXTERN(json);

GREATEST_MAIN_DEFS();

int main(int argc, char **argv)
{
  GREATEST_MAIN_BEGIN();

  RUN_SUITE(json);

  GREATEST_MAIN_END();
}
