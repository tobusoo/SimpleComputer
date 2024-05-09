#include <stdio.h>

#include <myBigChars.h>
#include <mySimpleComputer.h>
#include <myTerm.h>

void
printFlags (void)
{
  int value = 0;
  mt_gotoXY (2, 87);

  sc_regGet (SC_OVERFLOW, &value);
  mt_print ("      %c ", value ? 'P' : '_');

  sc_regGet (SC_DIV_BY_ZERO, &value);
  mt_print ("%c ", value ? '0' : '_');

  sc_regGet (SC_OUT_OF_RANGE, &value);
  mt_print ("%c ", value ? 'M' : '_');

  sc_regGet (SC_IGNORE_CLOCK_PULSE, &value);
  mt_print ("%c ", value ? 'T' : '_');

  sc_regGet (SC_INVALID_COMMAND, &value);
  mt_print ("%c ", value ? 'E' : '_');
}