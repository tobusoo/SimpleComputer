#include <stdbool.h>

#include "sc_variables.h"

static int
forward_code (int x)
{
  bool sign = x >> 14;
  if (sign == 0)
    return x;

  x = (~(x - 1) | 0b1 << 14) & 0b111111111111111;
  return x == 0b100000000000000 ? 0 : x;
}

int
sc_accumulatorGet (int *value)
{
  if (!value)
    return -1;

  *value = forward_code (sc_accumulator);
  return 0;
}
