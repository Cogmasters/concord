#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "orka-utils.h"

int main(void)
{
  int64_t timestamp_ms = orka_timestamp_ms();
  printf("%ld\n", timestamp_ms);

  return 0;
}
