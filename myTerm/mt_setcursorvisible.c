#include <stdio.h>

int
mt_setcursorvisible (int value)
{
  if (value)
    printf ("\e[?25h\e[?8c");
  else
    printf ("\e[?25l\e[?1c");

  return 0;
}