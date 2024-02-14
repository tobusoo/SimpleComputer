#include <stdio.h>

#include "mySimpleComputer.h"

static void
print_bin (int value)
{
  for (int i = 15; i >= 1; i--)
    {
      printf ("%d", SC_BIT_GET (value, i));
    }
}

void
printDecodedCommand (int value)
{
  printf ("dec: %d | oct: %o | hex: %X | bin: ", value, value, value);
  print_bin (value);
}