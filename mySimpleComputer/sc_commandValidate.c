#include "mySimpleComputer.h"
#include "sc_variables.h"

int
sc_commandValidate (int command)
{
  if (command >> 7 || command < 0x00 || (command > 0x01 && command < 0x0A)
      || (command > 0x0B && command < 0x14)
      || (command > 0x15 && command < 0x1E)
      || (command > 0x21 && command < 0x28)
      || (command > 0x2B && command < 0x33) || (command > 0x4C))
    {
      SC_BIT_SET (sc_register, SC_INVALID_COMMAND);
      return -1;
    }

  return 0;
}