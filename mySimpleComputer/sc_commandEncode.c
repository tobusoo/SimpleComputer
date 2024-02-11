#include "mySimpleComputer.h"
#include "sc_variables.h"

int
sc_commandEncode (int sign, int command, int operand, int *value)
{
  if (!value)
    return -1;

  if (sign != 0)
    {
      SC_BIT_SET (sc_register, SC_INVALID_COMMAND);
      return -1;
    }

  if (operand >> 7)
    {
      SC_BIT_SET (sc_register, SC_OVERFLOW);
      return -1;
    }

  if (sc_commandValidate (command) == -1)
    return -1;

  *value = sign << 14 | command << 7 | operand;

  return 0;
}