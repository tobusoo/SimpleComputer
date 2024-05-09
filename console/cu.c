#include <time.h>
#include <unistd.h>

#include "console.h"
#include <myReadKey.h>
#include <mySimpleComputer.h>
#include <myTerm.h>

void
CPUINFO ()
{
  mt_gotoXY (26, 2);
  mt_print ("Бирюков Никита Андреевич, ИС-241");
  sleep (1);
  mt_gotoXY (26, 2);
  mt_print ("                                ");
}

void
READ (int address)
{
  struct timespec ts;
  ts.tv_nsec = 2000000;
  ts.tv_sec = 0;
  nanosleep (&ts, &ts);

  int value;
  printTerm (address, 1);
  nanosleep (&ts, &ts);
  mt_gotoXY (24, 73);
  mt_print ("     ");
  mt_gotoXY (24, 73);
  nanosleep (&ts, &ts);

  sc_regSet (SC_IGNORE_CLOCK_PULSE, 1);
  if (rk_readvalue (&value, 1000) == 0)
    sc_memorySet (address, value);
  sc_regSet (SC_IGNORE_CLOCK_PULSE, 0);
  updateTerm ();
  nanosleep (&ts, &ts);
}

void
WRITE (int address)
{
  struct timespec ts;
  ts.tv_nsec = 2000000;
  ts.tv_sec = 0;
  nanosleep (&ts, &ts);
  printTerm (address, 0);
  nanosleep (&ts, &ts);
}

void
LOAD (int address)
{
  int value;
  if (sc_memoryGet (address, &value) == -1)
    return;

  sc_accumulatorSet (value);
}

void
STORE (int address)
{
  int value;
  sc_accumulatorGet (&value);
  sc_memorySet (address, value);
}

int
JUMP (int address)
{
  return sc_icounterSet (address);
}

int
JNEG (int address)
{
  int value;
  sc_accumulatorGet (&value);
  if (value >> 14)
    return sc_icounterSet (address);
  return -1;
}

int
JZ (int address)
{
  int value;
  sc_accumulatorGet (&value);
  if (value == 0)
    return sc_icounterSet (address);
  return -1;
}

int
JNS (int address)
{
  int value;
  sc_accumulatorGet (&value);
  if (value >> 14 == 0 && value != 0)
    return sc_icounterSet (address);

  return -1;
}

void
HALT ()
{
  sc_regSet (SC_IGNORE_CLOCK_PULSE, 1);
  sc_icounterSet (0);
}

void
CU (void)
{
  int i_counter, memory, sign, command, operand, jump_result = 1;
  sc_icounterGet (&i_counter);

  if (sc_memoryGet (i_counter, &memory) == -1)
    {
      return;
    }

  if (sc_commandDecode (memory, &sign, &command, &operand) == -1)
    {
      sc_regSet (SC_INVALID_COMMAND, 1);
      sc_regSet (SC_IGNORE_CLOCK_PULSE, 1);
      return;
    }

  if (sc_commandValidate (command) == -1 || sign == 1)
    {
      sc_regSet (SC_INVALID_COMMAND, 1);
      sc_regSet (SC_IGNORE_CLOCK_PULSE, 1);
      return;
    }

  if ((command >= 0x1E && command <= 0x21)
      || (command >= 0x33 && command <= 0x36))
    ALU (command, operand);

  else
    {
      switch (command)
        {
        case 0x00: // NOP
          break;
        case 0x01: // CPUINFO
          CPUINFO ();
          break;
        case 0x0A: // READ
          READ (operand);
          break;
        case 0x0B: // WRITE
          WRITE (operand);
          break;
        case 0x14: // LOAD
          LOAD (operand);
          break;
        case 0x15: // STORE
          STORE (operand);
          break;
        case 0x28: // JUMP
          jump_result = JUMP (operand);
          break;
        case 0x29: // JNEG
          jump_result = JNEG (operand);
          break;
        case 0x2A: // JZ
          jump_result = JZ (operand);
          break;
        case 0x2B: // HALT
          HALT (operand);
          break;
        case 0x37: // JNS
          jump_result = JNS (operand);
          break;
        default:
          break;
        }
    }

  if (jump_result != 0)
    sc_icounterSet (i_counter + 1);
  printMemory ();
  printCommand ();
  printCounters ();
  printAccumulator ();
  printFlags ();
}