#include <stdio.h>

#include "mySimpleComputer.h"

void
printCell (int address)
{
  int value = 0;

  sc_memoryGet (address, &value);
  if (value >> 14)
    printf ("-");
  else
    printf ("+");

  printf ("%04X", value & 0b11111111111111);
}