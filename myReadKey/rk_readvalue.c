#include <ctype.h>
#include <myReadKey.h>
#include <myTerm.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool
check_char (char ch, int i)
{
  if (i == 0)
    return ch == '+' || ch == '-';

  return isdigit (ch) || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f');
}

void
decode (char *buf, int *value)
{
  int end = strtol (buf + 3, NULL, 16);
  end = end >= 0b1111111 ? 0b1111111 : end;
  buf[3] = 0;
  int begin = strtol (buf + 1, NULL, 16);
  begin = begin >= 0b1111111 ? 0b1111111 : begin;
  bool sign = buf[0] == '+' ? 0 : 1;

  *value = (sign << 14) | (begin << 7) | end;
}

int
rk_readvalue (int *value, int timeout)
{
  char buf[32] = { 0 };
  bool is_completed = false;
  int ret = 1;
  int i = 0;

  if (!value)
    return -1;
  if (rk_mytermsave () == -1)
    return -1;
  if (rk_mytermregime (0, timeout, 0, 0, 1) == -1)
    return -1;

  while (!is_completed && !ret == 0)
    {
      ret = read (STDIN_FILENO, buf + i, 4);
      if (strcmp (buf + i, "\E") == 0)
        return -1;
      if (check_char (buf[i], i))
        {
          mt_print ("%c", toupper (buf[i]));
          i++;
        }

      is_completed = i == 5;
    }

  if (is_completed)
    decode (buf, value);

  if (rk_mytermrestore () == -1)
    return -1;

  return is_completed == 1 ? 0 : -2;
}