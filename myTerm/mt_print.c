#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "myTerm.h"

int
mt_print (char *format, ...)
{
  char buffer[128] = { 0 };

  va_list arg_ptr;
  va_start (arg_ptr, format);
  vsnprintf (buffer, 128, format, arg_ptr);
  va_end (arg_ptr);

  size_t len = strlen (buffer);
  return write (STDOUT_FILENO, buffer, len) == -1 ? -1 : 0;
}