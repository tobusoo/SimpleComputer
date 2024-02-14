#include "sc_variables.h"

int
sc_icounterGet (int *value)
{
  if (!value)
    return -1;

  *value = sc_command_counter;
  return 0;
}
