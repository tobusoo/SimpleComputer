#include <sys/ioctl.h>

int
mt_getscreensize (int *rows, int *cols)
{
  if (!rows || !cols)
    return -1;
  struct winsize ws;
  if (ioctl (1, TIOCGWINSZ, &ws))
    {
      return -1;
    }

  *rows = ws.ws_row;
  *cols = ws.ws_col;
  return 0;
}