#include <stdio.h>
#include <stdlib.h>

#include "console.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

void
printAccumulator (void)
{
  int value;
  mt_gotoXY (2, 64);

  mt_print (" sc: ");
  sc_accumulatorGet (&value);
  if (value >> 14)
    mt_print ("-");
  else
    mt_print ("+");

  int command = (value >> 7) & 0b1111111;
  int operand = value & 0b1111111;
  mt_print ("%02X%02X ", command, operand);
  mt_print ("hex: %04X", value);
}