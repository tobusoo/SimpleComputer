#include <stdio.h>

#include "mySimpleComputer.h"

void
printCounters (void)
{
  int value;
  sc_icounterGet (&value);
  if (value >> 14)
    printf ("-");
  else
    printf ("+");

  printf ("%04X", value & 0b11111111111111);
}