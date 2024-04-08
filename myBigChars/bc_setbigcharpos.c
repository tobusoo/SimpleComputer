#include <myBigChars.h>
#include <mySimpleComputer.h>

int
bc_setbigcharpos (int *big, int x, int y, int value)
{
  if (!big || x < 0 || y < 0 || x >= 8 || y >= 8)
    return -1;

  int i = x < 4 ? 0 : 1;

  if (value)
    {
      SC_BIT_SET (big[i], x * 8 + y + 1);
    }
  else
    {
      SC_BIT_RM (big[i], x * 8 + y + 1);
    }

  return 0;
}