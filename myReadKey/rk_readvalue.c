#include <ctype.h>
#include <myReadKey.h>
#include <myTerm.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void
decode_from_buf (char *buf, int *value)
{
  int end = strtol (buf + 3, NULL, 16);
  end = end >= 0b1111111 ? 0b1111111 : end;
  buf[3] = 0;
  int begin = strtol (buf + 1, NULL, 16);
  begin = begin >= 0b1111111 ? 0b1111111 : begin;
  bool sign = buf[0] == '+' ? 0 : 1;

  *value = (sign << 14) | (begin << 7) | end;
}

bool
is_correct_key_at_i_position (enum keys key, int i)
{
  if (i == 0)
    return key == KEY_PLUS || key == KEY_MINUS;

  return key >= KEY_0 && key <= KEY_F;
}

int
rk_readvalue (int *value, int timeout)
{
  char buf[5] = { 0 };
  bool is_completed = false;
  int ret = 0;
  int i = 0;
  enum keys key;

  if (!value)
    return -1;
  if (rk_mytermsave () == -1)
    return -1;
  if (rk_mytermregime (0, timeout, 0, 0, 1) == -1)
    return -1;

  while (!is_completed && ret != -1)
    {
      ret = rk_readkey (&key);
      if (key == KEY_ESC)
        return -1;
      if (is_correct_key_at_i_position (key, i))
        {
          if (key <= KEY_9)
            buf[i] = key + '0';
          else if (key <= KEY_F)
            buf[i] = key + 'A' - KEY_A;
          else if (key == KEY_MINUS)
            buf[i] = '-';
          else if (key == KEY_PLUS)
            buf[i] = '+';

          mt_print ("%c", buf[i]);
          i++;
        }

      is_completed = i == 5;
    }

  if (is_completed)
    decode_from_buf (buf, value);

  if (rk_mytermrestore () == -1)
    return -1;

  return is_completed == 1 ? 0 : -2;
}