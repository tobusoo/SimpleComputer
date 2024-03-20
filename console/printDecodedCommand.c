#include <stdio.h>

#include <myBigChars.h>
#include <mySimpleComputer.h>
#include <myTerm.h>

static void
print_bin (int value)
{
  for (int i = 15; i >= 1; i--)
    {
      mt_print ("%d", SC_BIT_GET (value, i));
    }
}

void
printDecodedCommand (int value)
{
  bc_box (16, 1, 59, 1, DEFAULT, DEFAULT, " Редактируемая ячейка (формат) ",
          RED, WHITE);
  mt_gotoXY (17, 2);
  mt_print ("dec: %d | oct: %o | hex: %X     bin: ", value, value, value);
  print_bin (value);
  mt_print ("\n");
}