#include <stdio.h>
#include <stdlib.h>

#include "mySimpleComputer.h"

void
printAccumulator (void)
{
  int value;
  sc_accumulatorGet (&value);
  if (value >> 14)
    printf ("-");
  else
    printf ("+");

  printf ("%04X", value & 0b11111111111111);
}