#include <stdio.h>

#include <myBigChars.h>
#include <mySimpleComputer.h>
#include <myTerm.h>

void
printCounters (void)
{
  bc_box (4, 62, 21, 1, DEFAULT, DEFAULT, " Счетчик  команд ", RED, BLACK);
  int value;
  mt_gotoXY (5, 63);

  sc_icounterGet (&value);
  mt_print ("      IC: ");
  if (value >> 14)
    mt_print ("-");
  else
    mt_print ("+");

  int command = (value >> 7) & 0b1111111;
  int operand = value & 0b1111111;
  mt_print ("%02X%02X", command, operand);
}