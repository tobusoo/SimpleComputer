#include "mySimpleComputer.h"
#include "sc_variables.h"

int
sc_memoryGet (int address, int *value)
{
  if (!value)
    {
      return -1;
    }
  if (address >= SC_MEMORY_SIZE || address < 0)
    {
      SC_BIT_SET (sc_register, SC_OUT_OF_RANGE);
      return -1;
    }

  *value = sc_memory[address];
  return 0;
}
