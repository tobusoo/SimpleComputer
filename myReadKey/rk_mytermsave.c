#include <myReadKey.h>
#include <string.h>
#include <unistd.h>

#include "rk_variables.h"

int
rk_mytermsave (void)
{
  tcgetattr (STDIN_FILENO, &rk_current);
  memcpy (&rk_backup, &rk_current, sizeof (struct termios));

  return 0;
}