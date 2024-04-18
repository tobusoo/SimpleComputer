#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_COLOR "\e[0m"
#define RED_COLOR "\e[1;31m"
#define RED_COLOR_STR(string) "\e[1;31m" string DEFAULT_COLOR
#define MAGENTA_COLOR_STR(string) "\e[1;35m" string DEFAULT_COLOR

void
print_usage (const char *app_name)
{
  fprintf (stderr, "Usage: %s <in.sa> <out.o>\n", app_name);
}

char *
skip_space (char *string)
{
  while (*string == ' ')
    string++;
  return string;
}

int
get_lexems (char **lexems, char *str)
{
  int str_len = strlen (str);
  str[str_len - 1] = '\0';

  int lexem_count = 0;
  char *lexem = strtok (str, " ");
  char *delem;

  while (lexem != NULL)
    {
      lexems[lexem_count++] = lexem;
      delem = lexem_count == 3 ? "\n" : " ";
      lexem = strtok (NULL, delem);
    }

  return (lexem_count == 3 || lexem_count == 4) ? 0 : -1;
}

int
get_command (char *command, int *value)
{
  if (strcmp (command, "NOP") == 0)
    *value = 0x00;
  else if (strcmp (command, "CPUINFO") == 0)
    *value = 0x01;
  else if (strcmp (command, "READ") == 0)
    *value = 0x0A;
  else if (strcmp (command, "WRITE") == 0)
    *value = 0x0B;
  else if (strcmp (command, "LOAD") == 0)
    *value = 0x14;
  else if (strcmp (command, "STORE") == 0)
    *value = 0x15;
  else if (strcmp (command, "ADD") == 0)
    *value = 0x1E;
  else if (strcmp (command, "SUB") == 0)
    *value = 0x1F;
  else if (strcmp (command, "DIVIDE") == 0)
    *value = 0x20;
  else if (strcmp (command, "MUL") == 0)
    *value = 0x21;
  else if (strcmp (command, "JUMP") == 0)
    *value = 0x28;
  else if (strcmp (command, "JNEG") == 0)
    *value = 0x29;
  else if (strcmp (command, "JZ") == 0)
    *value = 0x2A;
  else if (strcmp (command, "HALT") == 0)
    *value = 0x2B;
  else if (strcmp (command, "NOT") == 0)
    *value = 0x33;
  else if (strcmp (command, "AND") == 0)
    *value = 0x34;
  else if (strcmp (command, "OR") == 0)
    *value = 0x35;
  else if (strcmp (command, "XOR") == 0)
    *value = 0x36;
  else if (strcmp (command, "=") == 0)
    return 1;
  else
    return -1; // INVALID COMMAND

  return 0;
}

int
get_value (char *buf, int *value)
{
  char *end = NULL;
  int len = strlen (buf);
  if (len != 5)
    return -1;

  int end_num = strtol (buf + 3, &end, 16);
  if (end == buf + 3 || (end_num == LONG_MAX || end_num == LONG_MIN)
      || end_num >> 7 != 0)
    return -1;

  buf[3] = '\0';

  int begin = strtol (buf + 1, &end, 16);
  if (end == buf + 1 || (begin == LONG_MAX || begin == LONG_MIN)
      || begin >> 7 != 0)
    return -1;

  if (buf[0] != '+' && buf[0] != '-')
    return -1;

  bool sign = buf[0] == '+' ? 0 : 1;
  *value = (sign << 14) | (begin << 7) | end_num;
  return 0;
}

int
strtonum (char *buf, int *value)
{
  char *end = NULL;
  int temp = strtol (buf, &end, 10);
  if (end == buf || (temp == LONG_MAX || temp == LONG_MIN))
    return -1;

  *value = temp;
  return 0;
}

void
print_error (char *str, char *reason, char *lexem, int line)
{
  fprintf (stderr, RED_COLOR_STR ("%d: %s\n"), line, str);
  fprintf (stderr,
           RED_COLOR_STR ("[ERROR]") " %s: " MAGENTA_COLOR_STR ("\"%s\"") "\n",
           reason, lexem);
  exit (EXIT_FAILURE);
}

bool
str_not_empty (char *str)
{
  for (int i = 0; str[i] != '\0'; i++)
    {
      if (str[i] != ' ' && str[i] != '\n')
        return true;
    }

  return false;
}

void
line_translation (char *buf, int line_num, int *memory)
{
  char lexems_buf[256];
  strcpy (lexems_buf, buf);

  int command_adr, command, operand, instruction = 0, value = 0;
  char *lexems[4] = { NULL };
  int res = get_lexems (lexems, lexems_buf);
  if (res == -1 && str_not_empty (buf))
    print_error (buf, "Parse error", "", line_num);
  else if (res == -1)
    return;

  res = strtonum (lexems[0], &command_adr);
  if (res == -1 || command_adr >= 128 || command_adr < 0)
    print_error (buf, "Invalid address", lexems[0], line_num);

  res = get_command (lexems[1], &command);
  if (res == -1)
    print_error (buf, "Invalid command", lexems[1], line_num);
  else if (res == 1)
    {
      res = get_value (lexems[2], &value);
      if (res == -1)
        print_error (buf, "Invalid value", lexems[2], line_num);
      instruction = value;
    }
  else
    {
      instruction |= command << 7;

      res = strtonum (lexems[2], &operand);
      if (res == -1 || operand >> 7 != 0)
        print_error (buf, "Invalid operand", lexems[2], line_num);

      instruction |= operand;
    }

  lexems[3] = skip_space (lexems[3]);
  if (lexems[3] != NULL && lexems[3][0] != ';' && str_not_empty (lexems[3]))
    print_error (buf, "Incorrect comment format ", lexems[3], line_num);

  memory[command_adr] = instruction;
}

void
file_translation (FILE *input, int *memory)
{
  if (!input)
    return;

  char buf[256] = { 0 };
  int line_num = 1;

  while (fgets (buf, sizeof (buf), input) != NULL)
    {
      line_translation (buf, line_num++, memory);
    }
}

int
main (int argc, char *argv[])
{
  FILE *input, *out;
  int memory[128] = { 0 };

  if (argc != 3)
    {
      print_usage (argv[0]);
      exit (EXIT_FAILURE);
    }

  input = fopen (argv[1], "r");
  if (!input)
    {
      fprintf (stderr, "Couldn't open \"%s\": ", argv[1]);
      perror (" ");
      exit (EXIT_FAILURE);
    }

  file_translation (input, memory);

  out = fopen (argv[2], "wb");
  if (!out)
    {
      fprintf (stderr, "Couldn't open \"%s\": ", argv[2]);
      perror (" ");
      fclose (input);
      exit (EXIT_FAILURE);
    }

  size_t n = fwrite (memory, sizeof (*memory), 128, out);
  if (n != 128)
    {
      fclose (input);
      fprintf (stderr, "Couldn't write programm to \"%s\": ", argv[2]);
      perror (" ");
      exit (EXIT_FAILURE);
    }

  fclose (input);
  fclose (out);
  return 0;
}