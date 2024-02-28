#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "console.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

void
print_memory ()
{
  int k = 0;
  for (size_t i = 0; i < 12; i++)
    {
      for (size_t j = 0; j < 10; j++)
        {
          printCell (k++, DEFAULT, DEFAULT);
          mt_print (" ");
        }
      mt_print ("\n");
    }
  for (size_t i = 0; i < 8; i++)
    {
      printCell (i + 120, DEFAULT, DEFAULT);
      mt_print (" ");
    }
  mt_print ("\n\n");
}

int
is_bad_term ()
{
  if (!isatty (0))
    {
      printf ("Поток ввода не связан с терминалом\n");
      return 1;
    }
  if (!isatty (1))
    {
      printf ("Поток вывода не связан с терминалом\n");
      return 1;
    }
  if (!isatty (2))
    {
      printf ("Поток вывода ошибок не связан с терминалом\n");
      return 1;
    }

  int rows, cols;
  mt_getscreensize (&rows, &cols);
  if (rows < 26 || cols < 110)
    {
      printf ("Размер терминала должен быть не меньше 26x110\n");
      return 1;
    }

  return 0;
}

int
main ()
{
  if (is_bad_term ())
    {
      return 1;
    }
  mt_clrscr ();

  sc_memoryInit ();
  sc_accumulatorInit ();
  sc_icounterInit ();
  sc_regInit ();

  size_t n = 128;
  for (size_t i = 0; i < n; i++)
    {
      sc_memorySet (i, i);
    }
  mt_clrscr ();
  print_memory ();
  printDecodedCommand (0x1A34);
  printAccumulator ();
  printFlags ();
  printCounters ();
  printCommand ();

  for (int i = 0; i < 7; i++)
    {
      int address = rand () % 128;
      printTerm (address, 0);
      sleep (1);
    }

  mt_print ("\n");
  mt_setdefaultcolor ();
  mt_gotoXY (44, 0);

  return 0;
}