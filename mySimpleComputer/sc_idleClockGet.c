#include "sc_variables.h"

int
sc_idleClockGet (int *value)
{
  if (!value)
    return -1;

  *value = sc_idle_clock;
  return 0;
}