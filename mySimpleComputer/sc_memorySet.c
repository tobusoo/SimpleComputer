#include "mySimpleComputer.h"
#include "sc_variables.h"

int
sc_memorySet (int address, int value)
{
  if (value >> 15)
    {
      SC_BIT_SET (sc_register, SC_OVERFLOW);
      return -1;
    }
  if (address >= SC_MEMORY_SIZE || address < 0)
    {
      SC_BIT_SET (sc_register, SC_OUT_OF_RANGE);
      return -1;
    }

  sc_memory[address] = value;
  return 0;
}
