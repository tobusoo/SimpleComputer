#include <myBigChars.h>
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <stdbool.h>

int
bc_printbigchar (int big[2], int x, int y, enum colors fg, enum colors bg)
{

  if (mt_gotoXY (x, y) == -1)
    return -1;
  mt_setfgcolor (fg);
  mt_setbgcolor (bg);

  bool bit = 0;
  int i = 1;
  for (int x2 = 0; x2 < 4; x2++)
    {
      for (int y = 0; y < 8; y++)
        {
          bit = SC_BIT_GET (big[0], i++);
          if (bit)
            {
              bc_printA ("a");
            }
          else
            {
              mt_print (" ");
            }
        }
      mt_gotoXY (x + x2 + 1, y);
    }

  i = 1;
  for (int x2 = 0; x2 < 4; x2++)
    {
      for (int y = 0; y < 8; y++)
        {
          bit = SC_BIT_GET (big[1], i++);
          if (bit)
            {
              bc_printA ("a");
            }
          else
            {
              mt_print (" ");
            }
        }
      mt_gotoXY (x + x2 + 5, y);
    }

  return 0;
}
