#include "mySimpleComputer.h"
#include "sc_variables.h"

int
sc_commandDecode (int value, int *sign, int *command, int *operand)
{
  if (!sign || !command || !operand)
    return -1;

  if (value >> 15)
    {
      SC_BIT_SET (sc_register, SC_INVALID_COMMAND);
      return -1;
    }

  int sign_temp = value >> 14;
  if (sign_temp != 0)
    {
      SC_BIT_SET (sc_register, SC_INVALID_COMMAND);
      return -1;
    }

  int command_temp = value >> 7;
  if (sc_commandValidate (command_temp) == -1)
    return -1;

  *sign = sign_temp;
  *command = command_temp;
  *operand = value & 0b1111111;
  return 0;
}