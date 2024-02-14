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

  int command = (value >> 7) & 0b1111111;
  int operand = value & 0b1111111;
  printf ("%02X%02X", command, operand);
}