#include "sc_variables.h"
#include <stdio.h>
#include <string.h>

int
sc_memoryLoad (char *filename)
{
  if (!filename)
    return -1;

  FILE *file = fopen (filename, "rb");
  if (!file)
    return -1;

  int temp_memory[SC_MEMORY_SIZE];
  size_t n = fread (temp_memory, sizeof (*temp_memory), SC_MEMORY_SIZE, file);
  if (n != SC_MEMORY_SIZE)
    {
      fclose (file);
      return -1;
    }

  memcpy (sc_memory, temp_memory, SC_MEMORY_SIZE);

  fclose (file);
  return 0;
}