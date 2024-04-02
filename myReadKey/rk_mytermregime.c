#include <myReadKey.h>
#include <string.h>
#include <unistd.h>

#include "rk_variables.h"

int
rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint)
{
  if (tcgetattr (STDIN_FILENO, &rk_current) != 0)
    {
      return -1;
    }
  if (regime)
    rk_current.c_lflag |= ICANON;
  else
    rk_current.c_lflag &= ~ICANON;

  if (!regime)
    {
      rk_current.c_cc[VTIME] = vtime;
      rk_current.c_cc[VMIN] = vmin;
    }
  if (echo)
    rk_current.c_lflag |= ECHO;
  else
    rk_current.c_lflag &= ~ECHO;

  if (sigint)
    rk_current.c_lflag |= ISIG;
  else
    rk_current.c_lflag &= ~ISIG;

  return tcsetattr (STDIN_FILENO, TCSANOW, &rk_current);
}