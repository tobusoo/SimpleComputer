#include "mySimpleComputer.h"
#include "sc_variables.h"

int
sc_regSet (int registr, int value)
{
  if (registr > SC_REG_FLAGS_N || registr < SC_OVERFLOW)
    {
      return -1;
    }

  if (value)
    {
      SC_BIT_SET (sc_register, registr);
    }
  else
    {
      SC_BIT_RM (sc_register, registr);
    }

  return 0;
}