#include "mySimpleComputer.h"
#include "sc_variables.h"

int
sc_icounterSet (int value)
{
  if (value >> 15)
    {
      SC_BIT_SET (sc_register, SC_OVERFLOW);
      return -1;
    }

  sc_command_counter = value;

  return 0;
}