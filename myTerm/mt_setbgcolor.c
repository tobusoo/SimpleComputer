#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "myTerm.h"

int
mt_setbgcolor (enum colors clr)
{
  char buf[16] = { 0 };
  if (clr == DEFAULT)
    snprintf (buf, sizeof (buf), "\e[%dm", 0);
  else
    snprintf (buf, sizeof (buf), "\e[%dm", 40 + (int)clr);

  return write (STDOUT_FILENO, buf, sizeof (buf)) == -1 ? -1 : 0;
}