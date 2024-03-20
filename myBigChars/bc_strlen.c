#include <myBigChars.h>
#include <string.h>

int
bc_strlen (char *str)
{
  if (!str)
    return 0;

  int len = 0;
  int n_byte = strlen (str);
  char byte = 0;

  for (int i = 0; i < n_byte; len++)
    {
      byte = str[i];
      if ((byte & 0x80) == 0)
        i++;
      else if ((byte & 0xE0) == 0xC0)
        {
          i++;
          byte = str[i];
          if ((byte & 0xC0) == 0x80)
            i++;
          else
            return 0;
        }
      else if ((byte & 0xF0) == 0xE0)
        {
          i++;
          for (int j = 0; j < 2; j++)
            {
              byte = str[i];
              if ((byte & 0xC0) == 0x80)
                i++;
              else
                return 0;
            }
        }
      else if ((byte & 0xF8) == 0xF0)
        {
          i++;
          for (int j = 0; j < 3; j++)
            {
              byte = str[i];
              if ((byte & 0xC0) == 0x80)
                i++;
              else
                return 0;
            }
        }
    }

  return len;
}