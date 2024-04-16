#include <signal.h>

#include "console.h"
#include <mySimpleComputer.h>

void
IRC (int signum)
{
  if (signum == SIGUSR1)
    {
      sc_memoryInit ();
      sc_regInit ();
      sc_accumulatorInit ();
      sc_icounterInit ();
      sc_regSet (SC_IGNORE_CLOCK_PULSE, 1);
    }
  if (signum == SIGALRM)
    {
      int flag;
      sc_regGet (SC_IGNORE_CLOCK_PULSE, &flag);
      if (flag)
        return;
      CU ();
    }
}