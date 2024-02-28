#include <stdio.h>
#include <unistd.h>

int
mt_delline (void)
{
  fflush (stdin);
  char buf[] = "\e[M";
  return write (STDOUT_FILENO, buf, sizeof (buf)) == -1 ? -1 : 0;
}