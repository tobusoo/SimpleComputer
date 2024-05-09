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
      int flag, idle_clock;
      sc_regGet (SC_IGNORE_CLOCK_PULSE, &flag);
      if (flag)
        return;
      sc_idleClockGet (&idle_clock);
      if (idle_clock > 0)
        {
          sc_idleClockSet (idle_clock - 1);
          printCounters ();
        }
      else
        {
          if (idle_clock == 0)
            printCache ();
          CU ();
          sc_idleClockGet (&idle_clock);
        }
    }
}