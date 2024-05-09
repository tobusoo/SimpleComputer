#include "sc_variables.h"

void
sc_cacheInit ()
{
  for (int i = 0; i < CACHE_LINES; i++)
    {
      cache[i].use = false;
      cache[i].number = -1;
      cache[i].priority = 0;
    }
}