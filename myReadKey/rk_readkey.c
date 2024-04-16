#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include <myReadKey.h>
#include <myTerm.h>

int
read_esc (char *buffer, enum keys *key)
{
  int num = read (STDIN_FILENO, buffer, 1);
  if (num == 0)
    {
      *key = KEY_ESC;
      return 1;
    }
  buffer[num] = '\0';
  bool is_correct_esc = true;

  if (buffer[0] == '[')
    {
      num = read (STDIN_FILENO, buffer + 1, 1);
      if (buffer[1] == 'A')
        *key = KEY_UP_ARROW;
      else if (buffer[1] == 'B')
        *key = KEY_DOWN_ARROW;
      else if (buffer[1] == 'C')
        *key = KEY_RIGHT_ARROW;
      else if (buffer[1] == 'D')
        *key = KEY_LEFT_ARROW;
      else if (buffer[1] == '1')
        {
          num = read (STDIN_FILENO, buffer + 2, 1);
          if (buffer[2] == '5' || buffer[2] == '7')
            {
              num = read (STDIN_FILENO, buffer + 3, 1);
              if (buffer[3] == '~')
                {
                  if (buffer[2] == '5')
                    *key = KEY_F5;
                  else
                    *key = KEY_F6;
                }
              else
                is_correct_esc = false;
            }
          else
            is_correct_esc = false;
        }
      else
        is_correct_esc = false;
    }
  else
    is_correct_esc = false;

  *key = is_correct_esc == true ? *key : KEY_UNKNOWN;
  return is_correct_esc == true ? 1 : -1;
}

int
rk_readkey (enum keys *key)
{
  char buffer[8] = { 0 };
  if (!key)
    return -1;

  int num = read (STDIN_FILENO, buffer, 1);
  int res = 0;
  buffer[num] = '\0';

  if (buffer[0] == 'i')
    *key = KEY_I;
  else if (buffer[0] == '+')
    *key = KEY_PLUS;
  else if (buffer[0] == '-')
    *key = KEY_MINUS;
  else if (buffer[0] == '0')
    *key = KEY_0;
  else if (buffer[0] == '1')
    *key = KEY_1;
  else if (buffer[0] == '2')
    *key = KEY_2;
  else if (buffer[0] == '3')
    *key = KEY_3;
  else if (buffer[0] == '4')
    *key = KEY_4;
  else if (buffer[0] == '5')
    *key = KEY_5;
  else if (buffer[0] == '6')
    *key = KEY_6;
  else if (buffer[0] == '7')
    *key = KEY_7;
  else if (buffer[0] == '8')
    *key = KEY_8;
  else if (buffer[0] == '9')
    *key = KEY_9;
  else if (buffer[0] == 'a' || buffer[0] == 'A')
    *key = KEY_A;
  else if (buffer[0] == 'b' || buffer[0] == 'B')
    *key = KEY_B;
  else if (buffer[0] == 'c' || buffer[0] == 'C')
    *key = KEY_C;
  else if (buffer[0] == 'd' || buffer[0] == 'D')
    *key = KEY_D;
  else if (buffer[0] == 'e' || buffer[0] == 'E')
    *key = KEY_E;
  else if (buffer[0] == 'f' || buffer[0] == 'F')
    *key = KEY_F;
  else if (buffer[0] == 'l' || buffer[0] == 'L')
    *key = KEY_L;
  else if (buffer[0] == 's' || buffer[0] == 'S')
    *key = KEY_S;
  else if (buffer[0] == 'r' || buffer[0] == 'R')
    *key = KEY_R;
  else if (buffer[0] == 't' || buffer[0] == 'T')
    *key = KEY_T;
  else if (buffer[0] == '\n')
    *key = KEY_ENTER;
  else if (buffer[0] == '\E')
    res = read_esc (buffer + 1, key);
  else
    *key = KEY_UNKNOWN;

  if (res == -1)
    return -1;

  return num == 0 ? -1 : 0;
}