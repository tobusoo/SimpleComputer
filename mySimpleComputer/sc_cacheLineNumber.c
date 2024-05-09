#include "sc_variables.h"

int
sc_cacheLineNumber (int i)
{
  if (i < 0 || i > 5)
    return -1;
  return cache[i].number;
}