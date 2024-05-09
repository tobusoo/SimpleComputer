#include "sc_variables.h"

int
sc_cacheGet (int cache_id, int addr_num)
{
  if (cache_id >= 5 || cache_id < 0 || addr_num < 0 || addr_num > 9)
    return -1;

  return cache[cache_id].values[addr_num];
}