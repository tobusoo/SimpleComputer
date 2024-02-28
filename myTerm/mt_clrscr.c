#include <unistd.h>

int
mt_clrscr (void)
{
  char buf[] = "\e[H\e[J";
  return write (STDOUT_FILENO, buf, sizeof (buf)) == -1 ? -1 : 0;
}