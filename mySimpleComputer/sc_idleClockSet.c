#include "sc_variables.h"

int
sc_idleClockSet (int value)
{
  sc_idle_clock = value;
  return 0;
}