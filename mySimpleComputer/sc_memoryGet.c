#include <stdbool.h>

#include "sc_variables.h"
#include <mySimpleComputer.h>

static int
forward_code (int x)
{
  bool sign = x >> 14;
  if (sign == 0)
    return x;

  x = (~(x - 1) | 0b1 << 14) & 0b111111111111111;
  return x == 0b100000000000000 ? 0 : x;
}

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

  if (sc_cache_ignore)
    *value = sc_memory[address];
  else
    {
      int cache_indx, addr_num;
      sc_memoryController (address, &cache_indx, &addr_num);
      *value = forward_code (cache[cache_indx].values[addr_num]);
    }
  return 0;
}
