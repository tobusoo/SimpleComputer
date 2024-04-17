#include <stdio.h>

int
mt_setcursorvisible (int value)
{
  if (value)
    printf ("\e[?25h");
  else
    printf ("\e[?25l");

  return 0;
}