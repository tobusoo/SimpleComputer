#include <stdio.h>

#include "mySimpleComputer.h"

void
printFlags (void)
{
  int value = 0;

  sc_regGet (SC_OVERFLOW, &value);
  printf ("%c ", value ? 'P' : '_');

  sc_regGet (SC_DIV_BY_ZERO, &value);
  printf ("%c ", value ? '0' : '_');

  sc_regGet (SC_OUT_OF_RANGE, &value);
  printf ("%c ", value ? 'M' : '_');

  sc_regGet (SC_IGNORE_CLOCK_PULSE, &value);
  printf ("%c ", value ? 'T' : '_');

  sc_regGet (SC_INVALID_COMMAND, &value);
  printf ("%c ", value ? 'E' : '_');
}