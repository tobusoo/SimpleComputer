#include <myBigChars.h>

int
bc_printA (char *str)
{
  if (!str)
    return -1;

  mt_print ("\e(0");
  mt_print (str);
  mt_print ("\e(B");

  return 0;
}