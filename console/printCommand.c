#include <myBigChars.h>
#include <mySimpleComputer.h>
#include <myTerm.h>

void
printCommand ()
{
  int address, value;
  sc_icounterGet (&address);
  mt_gotoXY (5, 88);

  if (address >= 128 || address < 0)
    mt_print ("     ! FF : FF");
  else
    {
      sc_cacheIgnore (1);
      sc_memoryGet (address, &value);
      sc_cacheIgnore (0);

      if (value >> 14)
        mt_print ("      -");
      else
        mt_print ("      +");
      int command = (value >> 7) & 0b1111111;
      int operand = value & 0b1111111;
      mt_print ("%02X : %02X", command, operand);
    }
}