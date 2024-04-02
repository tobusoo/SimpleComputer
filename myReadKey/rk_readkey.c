#include <myReadKey.h>
#include <myTerm.h>
#include <string.h>
#include <unistd.h>

int
rk_readkey (enum keys *key)
{
  char buffer[8] = { 0 };
  if (!key)
    return -1;

  if (rk_mytermsave () == -1)
    return -1;
  if (rk_mytermregime (0, 0, 1, 0, 1) == -1)
    return -1;

  int num = read (STDIN_FILENO, buffer, sizeof (buffer));
  buffer[num] = '\0';
  if (strcmp (buffer, "i") == 0)
    *key = KEY_I;
  else if (strcmp (buffer, "l") == 0)
    *key = KEY_L;
  else if (strcmp (buffer, "s") == 0)
    *key = KEY_S;
  else if (strcmp (buffer, "r") == 0)
    *key = KEY_R;
  else if (strcmp (buffer, "t") == 0)
    *key = KEY_T;
  else if (strcmp (buffer, "\E[15~") == 0 || strcmp (buffer, "\E[[E") == 0)
    *key = KEY_F5;
  else if (strcmp (buffer, "\E[17~") == 0)
    *key = KEY_F6;
  else if (strcmp (buffer, "\n") == 0)
    *key = KEY_ENTER;
  else if (strcmp (buffer, "\E[A") == 0)
    *key = KEY_UP_ARROW;
  else if (strcmp (buffer, "\E[B") == 0)
    *key = KEY_DOWN_ARROW;
  else if (strcmp (buffer, "\E[C") == 0)
    *key = KEY_RIGHT_ARROW;
  else if (strcmp (buffer, "\E[D") == 0)
    *key = KEY_LEFT_ARROW;
  else if (strcmp (buffer, "\E") == 0)
    *key = KEY_ESC;
  else
    *key = KEY_UNKNOWN;

  return rk_mytermrestore ();
}