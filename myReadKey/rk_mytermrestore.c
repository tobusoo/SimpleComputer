#include <myReadKey.h>
#include <string.h>
#include <unistd.h>

#include "rk_variables.h"

int
rk_mytermrestore (void)
{
  return tcsetattr (STDIN_FILENO, TCSANOW, &rk_backup);
}