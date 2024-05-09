#include <string.h>
#include <sys/time.h>

#include "sc_variables.h"
#include <mySimpleComputer.h>

int
sc_cacheHit (int line_number)
{
  for (int i = 0; i < CACHE_LINES; i++)
    {
      if (cache[i].use && cache[i].number == line_number)
        return i;
    }

  return -1;
}

int
sc_cacheLRU ()
{
  int max_priority = -1;
  int i_max_priority = -1;
  for (int i = 0; i < CACHE_LINES; i++)
    {
      if (cache[i].use == false)
        return i;
      if (max_priority < cache[i].priority)
        {
          max_priority = cache[i].priority;
          i_max_priority = i;
        }
    }

  return i_max_priority;
}

void
sc_cachePup (int last_used_line)
{
  for (int i = 0; i < CACHE_LINES; i++)
    {
      if (i != last_used_line)
        cache[i].priority++;
      else
        cache[i].priority = 0;
    }
}

void
sc_memoryController (int address, int *cache_indx, int *addr_num)
{
  int idle_clock = 0, values_cnt;
  *addr_num = address % 10;
  int line_number = address - *addr_num;
  *cache_indx = sc_cacheHit (line_number);

  if (*cache_indx == -1) // cache miss
    {
      *cache_indx = sc_cacheLRU ();
      values_cnt = line_number + 10 <= 127 ? 10 : 8;

      sc_idleClockGet (&idle_clock);
      sc_idleClockSet (idle_clock + 10);
      if (cache[*cache_indx].use == true)
        {
          memcpy (sc_memory + cache[*cache_indx].number,
                  cache[*cache_indx].values, sizeof (int) * values_cnt);
        }
      cache[*cache_indx].use = 1;
      cache[*cache_indx].priority = 0;
      cache[*cache_indx].number = line_number;
      memcpy (cache[*cache_indx].values, sc_memory + line_number,
              sizeof (int) * values_cnt);
    }

  sc_cachePup (*cache_indx);
}