#include <myBigChars.h>
#include <mySimpleComputer.h>
#include <myTerm.h>

#include <stdbool.h>

static struct
{
  int address;
  int value;
  bool input;
  bool is_full;
} in_out[5] = { 0 };

void
printTerm (int address, int input)
{
  int value;

  for (int i = 0; i < 4; i++)
    in_out[i] = in_out[i + 1];

  in_out[4].address = address;
  in_out[4].input = input;
  in_out[4].is_full = true;
  sc_memoryGet (address, &in_out[4].value);

  for (int i = 0; i < 5; i++)
    {
      mt_gotoXY (20 + i, 64);
      mt_print ("          ");
      if (in_out[i].is_full)
        {
          mt_gotoXY (20 + i, 64);
          mt_print ("%02d%c ", in_out[i].address, in_out[i].input ? '<' : '>');

          value = in_out[i].value;
          int command = (value >> 7) & 0b1111111;
          int operand = value & 0b1111111;
          if (in_out[i].address >= 100)
            mt_print ("%c%02X%02X", value >> 14 ? '-' : '+', command, operand);
          else
            mt_print (" %c%02X%02X", value >> 14 ? '-' : '+', command,
                      operand);
        }
    }
}

void
updateTerm ()
{
  sc_memoryGet (in_out[4].address, &in_out[4].value);
  mt_gotoXY (24, 64);
  mt_print ("%02d%c ", in_out[4].address, in_out[4].input ? '<' : '>');
  int value = in_out[4].value;

  int command = (value >> 7) & 0b1111111;
  int operand = value & 0b1111111;
  if (in_out[4].address >= 100)
    mt_print ("%c%02X%02X", value >> 14 ? '-' : '+', command, operand);
  else
    mt_print (" %c%02X%02X", value >> 14 ? '-' : '+', command, operand);
}