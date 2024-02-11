#include "mySimpleComputer.h"
#include "sc_variables.h"

int
sc_accumulatorSet (int value)
{
  if (value >> 15)
    {
      SC_BIT_SET (sc_register, SC_OVERFLOW);
      return -1;
    }

  sc_accumulator = value;
  return 0;
}