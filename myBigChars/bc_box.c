#include <myBigChars.h>
#include <myTerm.h>

int
bc_box (int x1, int y1, int x2, int y2, enum colors box_fg, enum colors box_bg,
        char *header, enum colors header_fg, enum colors header_bg)
{
  if (mt_gotoXY (x1, y1) == -1)
    return -1;

  mt_setfgcolor (box_fg);
  mt_setbgcolor (box_bg);
  bc_printA ("l");

  for (int i = 0; i < x2; i++)
    {
      bc_printA ("q");
    }
  bc_printA ("k");

  for (int i = x1 + 1, j = 0; j < y2; j++, i++)
    {
      mt_gotoXY (i, y1 + x2 + 1);
      bc_printA ("x");
    }

  for (int i = x1 + 1, j = 0; j < y2; j++, i++)
    {
      mt_gotoXY (i, y1);
      bc_printA ("x");
    }

  mt_gotoXY (x1 + y2 + 1, y1);
  bc_printA ("m");
  for (int i = 0; i < x2; i++)
    {
      bc_printA ("q");
    }
  bc_printA ("j");

  if (header)
    {
      int len = bc_strlen (header);
      int y_coord = y1 + x2 / 2 - len / 2 + 1;

      mt_setfgcolor (header_fg);
      mt_setbgcolor (header_bg);
      mt_gotoXY (x1, y_coord);
      mt_print ("%s", header);
    }
  mt_setdefaultcolor ();
  return 0;
}