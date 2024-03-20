#include <stdio.h>
#include <stdlib.h>

#include <myBigChars.h>
#include <mySimpleComputer.h>
#include <myTerm.h>

void
printAccumulator (void)
{
  bc_box (1, 62, 21, 1, DEFAULT, DEFAULT, " Аккумулятор ", RED, BLACK);
  int value;
  mt_gotoXY (2, 63);

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