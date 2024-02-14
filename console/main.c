#include <stdio.h>
#include <stdlib.h>

#include "console.h"
#include "mySimpleComputer.h"

void
print_memory ()
{
  int k = 0;
  for (size_t i = 0; i < 12; i++)
    {
      for (size_t j = 0; j < 10; j++)
        {
          printCell (k++);
          printf (" ");
        }
      printf ("\n");
    }
  for (size_t i = 0; i < 8; i++)
    {
      printCell (i + 120);
      printf (" ");
    }
  printf ("\n\n");
}

int
main ()
{

  sc_memoryInit ();
  sc_accumulatorInit ();
  sc_icounterInit ();
  sc_regInit ();

  size_t n = rand () % 128;
  for (size_t i = 0; i < n; i++)
    {
      sc_memorySet (rand () % 128, rand () % (0x7FFF));
    }
  print_memory ();

  char *memory_filename = "memory.data";
  printf ("result of sc_memorySave(\"memory.data\") = %d\n",
          sc_memorySave (memory_filename));
  sc_memoryInit ();
  print_memory ();

  printf ("result of sc_memoryLoad(\"memory.data\") = %d\n\n",
          sc_memoryLoad (memory_filename));
  print_memory ();

  printf ("result of sc_memorySet (0, 0x7FFF + 1) = %d\n",
          sc_memorySet (0, 0x7FFF + 1));

  sc_regSet (SC_DIV_BY_ZERO, 1);
  sc_regSet (SC_INVALID_COMMAND, 1);
  sc_regSet (SC_OUT_OF_RANGE, 1);
  printf ("\nSet all FLAGS:\n");
  printFlags ();
  printf ("\n\n");

  printf ("result of sc_regSet (32, 10)) = %d\n", sc_regSet (32, 10));
  printf ("\n");

  printf ("Set accumulator to 0x1A34\n");
  sc_accumulatorSet (0x1A34);
  printAccumulator ();
  printf ("\n\n");

  printf ("Result of sc_accumulatorSet (0xFFFF) = %d\n\n",
          sc_accumulatorSet (0xFFFF));

  printf ("Set counter to 0x1AFF\n");
  sc_icounterSet (0x1AFF);
  printCounters ();
  printf ("\n\n");

  printf ("Result of sc_icounterSet (0xFFFF) = %d\n\n",
          sc_icounterSet (0xFFFF));

  int value = 0, sign = 0, command = 0, operand = 0;

  printf ("print decoded value of accumulator:\n");
  sc_accumulatorGet (&value);
  printDecodedCommand (value);
  printf ("\n\n");
  printf ("print decoded value of memory[2]:\n");

  value = 0;
  sc_memoryGet (2, &value);
  sc_commandDecode (value, &sign, &command, &operand);
  printf ("sign = %d, command = %X, operand = %X\n", sign, command, operand);
  printDecodedCommand (value);
  printf ("\n\n");

  value = 0;
  printf ("Encode command (JUMP to 0xF): sign = 0, command = 0x28, operator = "
          "10\n");
  sc_commandEncode (0, 0x28, 0xF, &value);
  printDecodedCommand (value);
  printf ("\n");

  return 0;
}