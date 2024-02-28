#include <stdio.h>
#include <string.h>
#include <unistd.h>

int
mt_gotoXY (int x, int y)
{
  char buf[24] = { 0 };
  snprintf (buf, sizeof (buf), "\e[%d;%dH", x, y);
  return write (STDOUT_FILENO, buf, sizeof (buf)) == -1 ? -1 : 0;
}