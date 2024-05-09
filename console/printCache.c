#include <mySimpleComputer.h>

#include "console.h"

void
print_value (int value)
{
  int command, operand;
  command = (value >> 7) & 0b1111111;
  operand = value & 0b1111111;
  if (value >> 14)
    mt_print ("-");
  else
    mt_print ("+");
  mt_print ("%02X%02X", command, operand);
}

void
printCache (void)
{
  int line = 20, line_number, end, value;

  for (int i = 0; i < 5; i++)
    {
      mt_gotoXY (line, 2);
      line_number = sc_cacheLineNumber (i);
      if (line_number != -1)
        {
          if (line_number >= 100)
            mt_print ("%d: ", line_number);
          else
            mt_print ("%02d:  ", line_number);
          end = line_number != 120 ? 10 : 8;
          for (int j = 0; j < end - 1; j++)
            {
              value = sc_cacheGet (i, j);
              print_value (value);
              mt_print (" ");
            }
          value = sc_cacheGet (i, end - 1);
          print_value (value);
          line++;
        }
    }
  while (line <= 24)
    {
      mt_gotoXY (line, 2);
      mt_print ("%*.c", 64, ' ');
      line++;
    }
}
