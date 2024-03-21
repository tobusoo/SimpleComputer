#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "console.h"
#include <myBigChars.h>
#include <mySimpleComputer.h>
#include <myTerm.h>

int curr_address = 0;
int big[36] = { 0 };

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
  bc_box (1, 1, 59, 13, DEFAULT, DEFAULT, " Оперативная память ", RED, BLACK);
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
  if (rows < 26 || cols < 106)
    {
      printf ("Размер терминала должен быть не меньше 26x108\n");
      return 1;
    }

  return 0;
}

void
printBigCell (void)
{
  bc_box (7, 62, 43, 10, DEFAULT, DEFAULT,
          " Редактируемая ячейка (увеличено) ", RED, WHITE);
  int value;
  sc_memoryGet (curr_address, &value);

  if (value >> 14)
    bc_printbigchar (&big[34], 9, 64, DEFAULT, DEFAULT);
  else
    bc_printbigchar (&big[32], 9, 64, DEFAULT, DEFAULT);

  int num[4] = { 0 };
  int command = (value >> 7) & 0b1111111;
  int operand = value & 0b1111111;
  num[0] = command >> 4;
  num[1] = command & 0xf;
  num[2] = operand >> 4;
  num[3] = operand & 0xf;

  for (int i = 0; i < 4; i++)
    {
      bc_printbigchar (&big[num[i] * 2], 9, 71 + i * 9, DEFAULT, DEFAULT);
    }

  mt_setfgcolor (BLUE);
  mt_gotoXY (17, 63);
  mt_setbgcolor (BLACK);
  mt_print ("Номер редактируемой ячейки: %03d", curr_address);
  mt_setdefaultcolor ();
}

void
printKeys (void)
{
  bc_box (19, 75, 30, 5, DEFAULT, DEFAULT, " Клавиши ", GREEN, WHITE);
  mt_gotoXY (20, 76);
  mt_print ("l - load  s - save   i - reset");
  mt_gotoXY (21, 76);
  mt_print ("r - run   t - step");
  mt_gotoXY (22, 76);
  mt_print ("ESC - выход");
  mt_gotoXY (23, 76);
  mt_print ("F5 - accumulator");
  mt_gotoXY (24, 76);
  mt_print ("F6 - instruction counter");
}

void
printCache (void)
{
  bc_box (19, 1, 60, 5, DEFAULT, DEFAULT, " Кеш процессора ", GREEN, WHITE);
  mt_gotoXY (20, 2);
  mt_print ("in progress...");
}

int
main (int argc, char *argv[])
{
  int font_file, count;
  if (argc == 1)
    font_file = open ("font.bin", O_RDONLY);
  else if (argc == 2)
    font_file = open (argv[1], O_RDONLY);
  else
    {
      fprintf (stderr, "Usage: %s <font path>", argv[0]);
      return 1;
    }
  if (font_file == -1)
    {
      perror ("Could not open font file");
      return 1;
    }

  if (bc_bigcharread (font_file, big, 18, &count) == -1)
    {
      fprintf (stderr, "an error occurred while reading the file\n");
      return 1;
    }

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
  printDecodedCommand (0x1a34);
  printAccumulator ();
  printFlags ();
  printCounters ();
  printCommand ();
  sc_memorySet (0, 0x1a34);
  printBigCell ();
  printCache ();
  printKeys ();
  printCell (0, BLACK, WHITE);

  mt_setcursorvisible (0);
  for (int i = 0; i < 7; i++)
    {
      int address = rand () % 128;
      printTerm (address, 0);
      nanosleep (&(struct timespec){ .tv_sec = 0, .tv_nsec = 150000000 },
                 NULL);
    }

  mt_print ("\n");
  mt_setdefaultcolor ();
  mt_gotoXY (44, 0);
  mt_setcursorvisible (1);

  return 0;
}