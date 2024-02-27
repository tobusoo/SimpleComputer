#include <unistd.h>

int
mt_setdefaultcolor (void)
{
  char buf[] = "\e[0m";
  return write (STDOUT_FILENO, buf, sizeof (buf)) == -1 ? -1 : 0;
}
