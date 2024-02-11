#include "mySimpleComputer.h"
#include "sc_variables.h"

int
sc_regInit (void)
{
  SC_BIT_RM (sc_register, SC_OVERFLOW);
  SC_BIT_RM (sc_register, SC_DIV_BY_ZERO);
  SC_BIT_RM (sc_register, SC_OUT_OF_RANGE);
  SC_BIT_RM (sc_register, SC_INVALID_COMMAND);
  SC_BIT_SET (sc_register, SC_IGNORE_CLOCK_PULSE);

  return 0;
}