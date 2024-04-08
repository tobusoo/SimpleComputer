#include <myBigChars.h>
#include <mySimpleComputer.h>
#include <string.h>
#include <unistd.h>

int
bc_bigcharread (int fd, int *big, int need_count, int *count)
{
  if (!big || !count)
    return -1;

  int buf[2 * 18] = { 0 };
  ssize_t n = read (fd, buf, need_count * 2 * sizeof (int));
  if (n != need_count * 2 * sizeof (int))
    {
      *count = 0;
      return -1;
    }

  *count = need_count;
  memcpy (big, buf, need_count * 2 * sizeof (int));

  return 0;
}
