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

  int command = (value >> 7) & 0b1111111;
  int operand = value & 0b1111111;
  printf ("%02X%02X", command, operand);
}