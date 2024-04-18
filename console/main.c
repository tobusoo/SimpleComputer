#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "console.h"
#include <myBigChars.h>
#include <myReadKey.h>
#include <mySimpleComputer.h>
#include <myTerm.h>

#include <signal.h>
#include <sys/time.h>
#include <time.h>

struct termios default_term;

int curr_address = 0;
int row = 0, col = 0;
int big[36] = { 0 };

void
toAdress ()
{
  curr_address = row * 10 + col;
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
  sc_icounterGet (&value);
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
  printMemory ();
  int val;
  sc_memoryGet (curr_address, &val);

  printCell (curr_address, BLACK, WHITE);
  printBigCell ();
  printDecodedCommand (val);
  rk_mytermrestore ();
}

void
updateUI ()
{
  int cur_value;
  sc_memoryGet (curr_address, &cur_value);
  printCommand ();
  printDecodedCommand (cur_value);
  printBigCell ();
  printAccumulator ();
  printCounters ();
  printMemory ();
  printCell (curr_address, BLACK, WHITE);
  printFlags ();
}

void
reset ()
{
  sc_memoryInit ();
  sc_accumulatorInit ();
  sc_icounterInit ();
  sc_regInit ();

  row = 0;
  col = 0;
  toAdress ();
  printCell (curr_address, BLACK, WHITE);
  updateUI ();
}

void
draw_boxes ()
{
  bc_box (1, 1, 59, 13, DEFAULT, DEFAULT, " Оперативная память ", RED, BLACK);
  bc_box (1, 62, 21, 1, DEFAULT, DEFAULT, " Аккумулятор ", RED, BLACK);
  bc_box (1, 85, 20, 1, DEFAULT, DEFAULT, " Регистр флагов ", RED, BLACK);
  bc_box (4, 62, 21, 1, DEFAULT, DEFAULT, " Счетчик  команд ", RED, BLACK);
  bc_box (4, 85, 20, 1, DEFAULT, DEFAULT, " Команда ", RED, BLACK);
  bc_box (7, 62, 43, 10, DEFAULT, DEFAULT,
          " Редактируемая ячейка (увеличено) ", RED, WHITE);
  bc_box (19, 1, 60, 5, DEFAULT, DEFAULT, " Кеш процессора ", GREEN, WHITE);
  bc_box (19, 75, 30, 5, DEFAULT, DEFAULT, " Клавиши ", GREEN, WHITE);
  bc_box (19, 63, 10, 5, DEFAULT, DEFAULT, " IN--OUT ", GREEN, WHITE);
}

void
key_processing (bool *update_ui, bool *need_exit)
{
  enum keys key;
  rk_readkey (&key);
  *update_ui = key == KEY_UNKNOWN ? false : true;

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
      cell_redactor ();
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
    case KEY_R:
      sc_regSet (SC_IGNORE_CLOCK_PULSE, 0);
      break;
    case KEY_T:
      CU ();
      break;
    case KEY_F5:
      accum_redactor ();
      break;
    case KEY_F6:
      icounter_redactor ();
      break;
    case KEY_ESC:
      *need_exit = true;
      break;
    default:
      break;
    }
}

int
main (int argc, char *argv[])
{
  if (term_preprocessing (argc, argv) == 1)
    return 1;

  mt_setcursorvisible (1);
  sc_memoryInit ();
  sc_accumulatorInit ();
  sc_icounterInit ();
  sc_regInit ();

  signal (SIGALRM, IRC);
  signal (SIGUSR1, IRC);
  struct itimerval nval, oval;
  nval.it_interval.tv_sec = 0;
  nval.it_interval.tv_usec = 500000;
  nval.it_value.tv_sec = 1;
  nval.it_value.tv_usec = 0;
  setitimer (ITIMER_REAL, &nval, &oval);

  rk_mytermregime (0, 1, 0, 0, 1);
  bool need_exit = false;
  int is_not_running = true;
  bool update_ui = true;

  draw_boxes ();
  printCache ();
  printKeys ();
  updateUI (is_not_running);
  while (!need_exit)
    {
      if (update_ui)
        {
          updateUI ();
        }

      sc_regGet (SC_IGNORE_CLOCK_PULSE, &is_not_running);
      if (is_not_running)
        key_processing (&update_ui, &need_exit);
      else
        update_ui = false;
    }

  mt_setdefaultcolor ();
  mt_setcursorvisible (1);
  tcsetattr (STDIN_FILENO, TCSANOW, &default_term);
  mt_clrscr ();

  return 0;
}