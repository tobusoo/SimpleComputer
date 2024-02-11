#include "sc_variables.h"
#include <stdio.h>

int
sc_memorySave (char *filename)
{
  if (!filename)
    return -1;

  FILE *file = fopen (filename, "wb");
  if (!file)
    return -1;

  size_t n = fwrite (sc_memory, sizeof (*sc_memory), SC_MEMORY_SIZE, file);
  if (n != SC_MEMORY_SIZE)
    {
      fclose (file);
      return -1;
    }

  fclose (file);
  return 0;
}