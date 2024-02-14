#include "sc_variables.h"
#include <string.h>

int
sc_memoryInit (void)
{
  memset (sc_memory, 0, SC_MEMORY_SIZE * sizeof (*sc_memory));

  return 0;
}
