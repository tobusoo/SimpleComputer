#include "console.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

static struct
{
  int address;
  int input;
} in_out[4] = { 0 };

void
printTerm (int address, int input)
{
  int value;

  for (int i = 0; i < 3; i++)
    {
      in_out[i].address = in_out[i + 1].address;
      in_out[i].input = in_out[i + 1].input;
    }

  in_out[3].address = address;
  in_out[3].input = input;
  for (int i = 0; i < 4; i++)
    {
      mt_gotoXY (20 + i, 64);
      sc_memoryGet (in_out[i].address, &value);
      mt_print ("%02d%c ", in_out[i].address, in_out[i].input ? '<' : '>');
      if (value >> 14)
        mt_print ("-");
      else
        mt_print ("+");

      int command = (value >> 7) & 0b1111111;
      int operand = value & 0b1111111;
      mt_print ("%02X%02X", command, operand);
    }
}
