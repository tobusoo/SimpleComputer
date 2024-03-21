#include <myBigChars.h>
#include <mySimpleComputer.h>

int
bc_getbigcharpos (int *big, int x, int y, int *value)
{
  if (!big || !value || x < 0 || y < 0 || x >= 8 || y >= 8)
    return -1;

  int i = x < 4 ? 0 : 1;
  *value = SC_BIT_GET (big[i], x * 8 + y + 1);

  return 0;
}