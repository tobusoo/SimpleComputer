#include "mySimpleComputer.h"
#include "myTerm.h"

void
printCell (int address, enum colors fg, enum colors bg)
{
  int value = 0;
  mt_setfgcolor (fg);
  mt_setbgcolor (bg);
  mt_gotoXY (address / 10 + 2, 6 * (address % 10) + 2);
  sc_memoryGet (address, &value);
  if (value >> 14)
    mt_print ("-");
  else
    mt_print ("+");

  int command = (value >> 7) & 0b1111111;
  int operand = value & 0b1111111;
  mt_print ("%02X%02X", command, operand);
  mt_setdefaultcolor ();
}