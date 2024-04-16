#include "console.h"

void
printMemory ()
{
  int k = 0;
  for (int i = 0; i < 12; i++)
    {
      for (int j = 0; j < 9; j++)
        {
          printCell (k++, DEFAULT, DEFAULT);
          mt_print (" ");
        }
      printCell (k++, DEFAULT, DEFAULT);
      mt_print ("\n");
    }
  for (int i = 0; i < 8; i++)
    {
      printCell (i + 120, DEFAULT, DEFAULT);
      mt_print (" ");
    }
}