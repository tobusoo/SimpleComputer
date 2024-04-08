#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include "console.h"
#include <myBigChars.h>
#include <myReadKey.h>
#include <mySimpleComputer.h>
#include <myTerm.h>

struct termios default_term;

int curr_address = 0;
int prev_address = 0;
int row = 0, col = 0;
int big[36] = { 0 };

void
toAdress ()
{
  curr_address = row * 10 + col;
}

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
term_preprocessing (int argc, char *argv[])
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

  tcgetattr (STDIN_FILENO, &default_term);
  return 0;
}

void
accum_redactor ()
{
  int value;
  mt_gotoXY (2, 68);
  mt_print ("     ");
  mt_gotoXY (2, 68);

  int ret = rk_readvalue (&value, 100);
  if (ret == 0)
    sc_accumulatorSet (value);
  printAccumulator ();
}

void
icounter_redactor ()
{
  int value;
  mt_gotoXY (5, 73);
  mt_print ("     ");
  mt_gotoXY (5, 73);

  int ret = rk_readvalue (&value, 100);
  if (ret == 0)
    sc_icounterSet (value);
  printCounters ();
}

int
cell_redactor ()
{
  int value;
  mt_gotoXY (row + 2, col * 6 + 2);
  mt_print ("     ");
  mt_gotoXY (row + 2, col * 6 + 2);

  int ret = rk_readvalue (&value, 10);
  if (ret == 0)
    sc_memorySet (curr_address, value);

  return ret;
}

void
store_memory ()
{
  char filename[64] = { 0 };
  rk_mytermsave ();
  rk_mytermregime (1, 0, 0, 1, 1);
  mt_gotoXY (26, 2);
  mt_print ("Enter filename for store memory: ");
  int n = read (STDIN_FILENO, filename, sizeof (filename));
  filename[n - 1] = '\0';

  sc_memorySave (filename);
  mt_gotoXY (26, 2);
  mt_print ("%*c", 100, ' ');

  rk_mytermrestore ();
}

void
load_memory ()
{
  char filename[64] = { 0 };
  rk_mytermsave ();
  rk_mytermregime (1, 0, 0, 1, 1);
  mt_gotoXY (26, 2);
  mt_print ("Enter filename for load memory: ");
  int n = read (STDIN_FILENO, filename, sizeof (filename));
  filename[n - 1] = '\0';

  sc_memoryLoad (filename);
  mt_gotoXY (26, 2);
  mt_print ("%*c", 100, ' ');
  print_memory ();

  int val;
  sc_memoryGet (curr_address, &val);

  printCell (curr_address, BLACK, WHITE);
  printBigCell ();
  printDecodedCommand (val);
  rk_mytermrestore ();
}

void
reset ()
{
  sc_memoryInit ();
  sc_accumulatorInit ();
  sc_icounterInit ();
  sc_regInit ();

  print_memory ();
  printAccumulator ();
  printFlags ();
  printCounters ();
  printCommand ();
  printBigCell ();
  printCache ();
  printKeys ();

  row = 0;
  col = 0;
  toAdress ();
  printCell (curr_address, BLACK, WHITE);
  printTerm (0, 0);
}

int
main (int argc, char *argv[])
{
  if (term_preprocessing (argc, argv) == 1)
    return 1;

  sc_memoryInit ();
  sc_accumulatorInit ();
  sc_icounterInit ();
  sc_regInit ();

  size_t n = 128;
  for (size_t i = 0; i < n; i++)
    {
      sc_memorySet (i, i);
    }

  print_memory ();
  printAccumulator ();
  printFlags ();
  printCounters ();
  printCommand ();
  sc_memorySet (0, 0x1a34);
  printBigCell ();
  printCache ();
  printKeys ();
  printCell (curr_address, BLACK, WHITE);
  mt_setcursorvisible (0);

  bool need_exit = false;
  bool change_cell = false;
  enum keys key;
  int cur_value;
  sc_memoryGet (curr_address, &cur_value);
  printDecodedCommand (cur_value);

  rk_mytermregime (0, 0, 1, 0, 1);
  printTerm (0, 0);

  while (!need_exit)
    {
      rk_readkey (&key);
      printCell (curr_address, DEFAULT, DEFAULT);
      switch (key)
        {
        case KEY_DOWN_ARROW:
          if (col == 8 || col == 9)
            row = row + 1 < 12 ? row + 1 : 0;
          else
            row = row + 1 < 13 ? row + 1 : 0;
          toAdress ();
          break;
        case KEY_UP_ARROW:
          if (col == 8 || col == 9)
            row = row - 1 >= 0 ? row - 1 : 11;
          else
            row = row - 1 >= 0 ? row - 1 : 12;

          toAdress ();
          break;
        case KEY_LEFT_ARROW:
          if (row == 12)
            col = col - 1 >= 0 ? col - 1 : 7;
          else
            col = col - 1 >= 0 ? col - 1 : 9;

          toAdress ();
          break;
        case KEY_RIGHT_ARROW:
          if (row == 12)
            col = col + 1 < 8 ? col + 1 : 0;
          else
            col = col + 1 < 10 ? col + 1 : 0;

          toAdress ();
          break;
        case KEY_ENTER:
          change_cell = cell_redactor ();
          break;
        case KEY_S:
          store_memory ();
          break;
        case KEY_L:
          load_memory ();
          break;
        case KEY_I:
          reset ();
          break;
        case KEY_F5:
          accum_redactor ();
          break;
        case KEY_F6:
          icounter_redactor ();
          break;
        case KEY_ESC:
          need_exit = true;
          break;
        default:
          break;
        }
      sc_memoryGet (curr_address, &cur_value);

      if (curr_address != prev_address)
        {
          printCell (curr_address, BLACK, WHITE);
          printBigCell ();
          printDecodedCommand (cur_value);
        }
      if (change_cell)
        {
          change_cell = false;
          printTerm (curr_address, 1);
        }
    }

  mt_setdefaultcolor ();
  mt_setcursorvisible (1);
  tcsetattr (STDIN_FILENO, TCSANOW, &default_term);
  mt_clrscr ();

  return 0;
}