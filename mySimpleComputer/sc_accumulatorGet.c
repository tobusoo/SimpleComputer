#include "sc_variables.h"

int
sc_accumulatorGet (int *value)
{
  if (!value)
    return -1;

  *value = sc_accumulator;
  return 0;
}
