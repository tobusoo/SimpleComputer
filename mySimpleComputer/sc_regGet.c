#include "mySimpleComputer.h"
#include "sc_variables.h"

int
sc_regGet (int registr, int *value)
{
  if (!value || registr > SC_REG_FLAGS_N || registr < SC_OVERFLOW)
    {
      return -1;
    }

  *value = SC_BIT_GET (sc_register, registr);
  return 0;
}