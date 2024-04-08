#include <myBigChars.h>
#include <mySimpleComputer.h>
#include <unistd.h>

int
bc_bigcharwrite (int fd, int *big, int count)
{
  if (!big)
    return -1;

  return write (fd, big, count * 2 * sizeof (int)) == -1 ? -1 : 0;
}