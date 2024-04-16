#include "mySimpleComputer.h"
#include "sc_variables.h"

int
sc_icounterSet (int value)
{
  if (0 > value || value > 127)
    {
      SC_BIT_SET (sc_register, SC_OVERFLOW);
      SC_BIT_SET (sc_register, SC_IGNORE_CLOCK_PULSE);
      return -1;
    }

  sc_command_counter = value;

  return 0;
}