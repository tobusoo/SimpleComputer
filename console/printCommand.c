#include <myBigChars.h>
#include <mySimpleComputer.h>
#include <myTerm.h>

void
printCommand ()
{
  bc_box (4, 85, 20, 1, DEFAULT, DEFAULT, " Команда ", RED, BLACK);

  int address, value;
  sc_icounterGet (&address);
  mt_gotoXY (5, 88);

  if (address >= 128 || address < 0)
    {
      mt_print ("! FF : FF");
    }
  else
    {
      sc_memoryGet (address, &value);
      if (value >> 14)
        mt_print ("    -");
      else
        mt_print ("    +");
      int command = (value >> 7) & 0b1111111;
      int operand = value & 0b1111111;
      mt_print ("%02X : %02X", command, operand);
    }
}