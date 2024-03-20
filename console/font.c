#include <myBigChars.h>
#include <stdio.h>

void
generate_0 (int *big)
{
  for (int i = 0; i < 8; i++)
    {
      bc_setbigcharpos (big, i, 2, 1);
      bc_setbigcharpos (big, i, 3, 1);
      bc_setbigcharpos (big, i, 6, 1);
      bc_setbigcharpos (big, i, 7, 1);
    }
  for (int i = 3; i < 6; i++)
    {
      bc_setbigcharpos (big, 0, i, 1);
      bc_setbigcharpos (big, 1, i, 1);
      bc_setbigcharpos (big, 6, i, 1);
      bc_setbigcharpos (big, 7, i, 1);
    }
}

void
generate_1 (int *big)
{
  bc_setbigcharpos (big, 0, 2, 1);
  bc_setbigcharpos (big, 1, 2, 1);
  bc_setbigcharpos (big, 1, 1, 1);
  bc_setbigcharpos (big, 7, 2, 1);
  bc_setbigcharpos (big, 7, 1, 1);
  bc_setbigcharpos (big, 7, 5, 1);
  bc_setbigcharpos (big, 7, 6, 1);
  for (size_t i = 0; i < 8; i++)
    {
      bc_setbigcharpos (big, i, 4, 1);
      bc_setbigcharpos (big, i, 3, 1);
    }
}

void
generate_2 (int *big)
{
  bc_setbigcharpos (big, 0, 2, 1);
  bc_setbigcharpos (big, 0, 3, 1);
  bc_setbigcharpos (big, 0, 4, 1);
  for (int i = 0; i < 5; i++)
    bc_setbigcharpos (big, 1, 1 + i, 1);
  bc_setbigcharpos (big, 1, 0, 1);
  bc_setbigcharpos (big, 2, 0, 1);
  bc_setbigcharpos (big, 2, 1, 1);
  bc_setbigcharpos (big, 2, 4, 1);
  bc_setbigcharpos (big, 2, 5, 1);

  bc_setbigcharpos (big, 3, 4, 1);
  bc_setbigcharpos (big, 3, 5, 1);
  bc_setbigcharpos (big, 4, 3, 1);
  bc_setbigcharpos (big, 4, 4, 1);
  bc_setbigcharpos (big, 5, 2, 1);
  bc_setbigcharpos (big, 5, 3, 1);
  bc_setbigcharpos (big, 5, 4, 1);
  bc_setbigcharpos (big, 6, 1, 1);
  bc_setbigcharpos (big, 6, 2, 1);
  bc_setbigcharpos (big, 6, 3, 1);
  for (int i = 0; i < 7; i++)
    bc_setbigcharpos (big, 7, i, 1);
}

void
generate_3 (int *big)
{
  for (int i = 2; i <= 7; i++)
    {
      bc_setbigcharpos (big, 0, i, 1);
      bc_setbigcharpos (big, 7, i, 1);
    }
  bc_setbigcharpos (big, 1, 1, 1);
  bc_setbigcharpos (big, 1, 2, 1);
  bc_setbigcharpos (big, 1, 3, 1);
  bc_setbigcharpos (big, 1, 6, 1);
  bc_setbigcharpos (big, 1, 7, 1);

  bc_setbigcharpos (big, 6, 1, 1);
  bc_setbigcharpos (big, 6, 2, 1);
  bc_setbigcharpos (big, 6, 3, 1);

  for (int i = 3; i <= 7; i++)
    {
      bc_setbigcharpos (big, 3, i, 1);
      bc_setbigcharpos (big, 4, i, 1);
    }

  for (int i = 1; i < 8; i++)
    {
      bc_setbigcharpos (big, i, 6, 1);
      bc_setbigcharpos (big, i, 7, 1);
    }
}

void
generate_4 (int *big)
{
  for (int i = 0; i < 8; i++)
    {
      bc_setbigcharpos (big, i, 6, 1);
      bc_setbigcharpos (big, i, 5, 1);
    }
  for (int i = 3; i < 7; i++)
    {
      bc_setbigcharpos (big, 4, i, 1);
      bc_setbigcharpos (big, 5, i, 1);
    }

  for (int i = 0; i < 6; i++)
    {
      bc_setbigcharpos (big, i, 2, 1);
      bc_setbigcharpos (big, i, 3, 1);
    }
}

void
generate_5 (int *big)
{
  for (int i = 1; i < 6; i++)
    {
      bc_setbigcharpos (big, 0, i, 1);
      bc_setbigcharpos (big, 1, i, 1);
      bc_setbigcharpos (big, 3, i, 1);
      bc_setbigcharpos (big, 4, i, 1);
      bc_setbigcharpos (big, 6, i, 1);
      bc_setbigcharpos (big, 7, i, 1);
    }

  bc_setbigcharpos (big, 2, 1, 1);
  bc_setbigcharpos (big, 2, 2, 1);
  bc_setbigcharpos (big, 5, 4, 1);
  bc_setbigcharpos (big, 5, 5, 1);
}

void
generate_6 (int *big)
{
  for (int i = 1; i < 7; i++)
    {
      bc_setbigcharpos (big, 0, i, 1);
      bc_setbigcharpos (big, 3, i, 1);
      bc_setbigcharpos (big, 6, i, 1);
      bc_setbigcharpos (big, 7, i, 1);
    }

  for (int i = 0; i < 8; i++)
    {
      bc_setbigcharpos (big, i, 1, 1);
      bc_setbigcharpos (big, i, 2, 1);
    }
  bc_setbigcharpos (big, 1, 6, 1);
  bc_setbigcharpos (big, 1, 5, 1);
  bc_setbigcharpos (big, 4, 5, 1);
  bc_setbigcharpos (big, 4, 6, 1);
  bc_setbigcharpos (big, 5, 5, 1);
  bc_setbigcharpos (big, 5, 6, 1);
}

void
generate_7 (int *big)
{
  for (int i = 1; i < 7; i++)
    {
      bc_setbigcharpos (big, 0, i, 1);
      bc_setbigcharpos (big, 1, i, 1);
    }

  bc_setbigcharpos (big, 2, 5, 1);
  bc_setbigcharpos (big, 2, 6, 1);
  bc_setbigcharpos (big, 3, 4, 1);
  bc_setbigcharpos (big, 3, 5, 1);
  bc_setbigcharpos (big, 4, 3, 1);
  bc_setbigcharpos (big, 4, 4, 1);
  for (int i = 5; i < 8; i++)
    {
      bc_setbigcharpos (big, i, 2, 1);
      bc_setbigcharpos (big, i, 3, 1);
    }
  bc_setbigcharpos (big, 1, 4, 0);
  bc_setbigcharpos (big, 1, 3, 0);
}

void
generate_8 (int *big)
{
  generate_0 (big);
  for (int i = 1; i < 8; i++)
    {
      bc_setbigcharpos (big, 3, i, 1);
      bc_setbigcharpos (big, 4, i, 1);
    }
}

void
generate_9 (int *big)
{
  generate_8 (big);
  for (int i = 1; i < 6; i++)
    {
      bc_setbigcharpos (big, 5, i, 0);
      bc_setbigcharpos (big, 6, i, 0);
    }
}

void
generate_a (int *big)
{
  for (int i = 2; i < 8; i++)
    {
      bc_setbigcharpos (big, i, 1, 1);
      bc_setbigcharpos (big, i, 2, 1);
      bc_setbigcharpos (big, i, 5, 1);
      bc_setbigcharpos (big, i, 6, 1);
    }
  bc_setbigcharpos (big, 0, 3, 1);
  bc_setbigcharpos (big, 0, 4, 1);
  bc_setbigcharpos (big, 1, 2, 1);
  bc_setbigcharpos (big, 1, 3, 1);
  bc_setbigcharpos (big, 1, 4, 1);
  bc_setbigcharpos (big, 1, 5, 1);
  for (int i = 4; i < 6; i++)
    {
      bc_setbigcharpos (big, i, 3, 1);
      bc_setbigcharpos (big, i, 4, 1);
    }
}

void
generate_b (int *big)
{
  generate_8 (big);
  bc_setbigcharpos (big, 0, 7, 0);
  bc_setbigcharpos (big, 7, 7, 0);
  for (int i = 0; i < 8; i++)
    {
      bc_setbigcharpos (big, i, 0, 0);
      bc_setbigcharpos (big, i, 2, 1);
    }
}

void
generate_c (int *big)
{
  generate_0 (big);
  for (int i = 2; i < 6; i++)
    {
      bc_setbigcharpos (big, i, 7, 0);
      bc_setbigcharpos (big, i, 6, 0);
    }
}

void
generate_d (int *big)
{
  generate_0 (big);
  bc_setbigcharpos (big, 0, 7, 0);
  bc_setbigcharpos (big, 7, 7, 0);
}

void
generate_e (int *big)
{
  generate_5 (big);
  for (int i = 0; i < 8; i++)
    {
      bc_setbigcharpos (big, i, 1, 1);
    }

  bc_setbigcharpos (big, 5, 5, 0);
  bc_setbigcharpos (big, 5, 4, 0);
  bc_setbigcharpos (big, 5, 2, 1);
  bc_setbigcharpos (big, 5, 3, 1);
  bc_setbigcharpos (big, 2, 3, 0);
  bc_setbigcharpos (big, 5, 3, 0);
}

void
generate_f (int *big)
{
  generate_e (big);
  for (int i = 3; i < 8; i++)
    {
      bc_setbigcharpos (big, 6, i, 0);
      bc_setbigcharpos (big, 7, i, 0);
    }
}

void
generate_plus (int *big)
{
  for (int i = 1; i < 7; i++)
    {
      bc_setbigcharpos (big, i, 3, 1);
      bc_setbigcharpos (big, i, 4, 1);
    }

  for (int i = 1; i < 7; i++)
    {
      bc_setbigcharpos (big, 3, i, 1);
      bc_setbigcharpos (big, 4, i, 1);
    }
}

void
generate_minus (int *big)
{
  for (int i = 1; i < 7; i++)
    {
      bc_setbigcharpos (big, 3, i, 1);
      bc_setbigcharpos (big, 4, i, 1);
    }
}

int
main ()
{
  FILE *file = fopen ("font.bin", "wb");
  if (!file)
    {
      fprintf (stderr, "Could not open font.bin\n");
      return 1;
    }

  int big[2 * 18] = { 0 };
  generate_0 (big);
  generate_1 (big + 2);
  generate_2 (big + 4);
  generate_3 (big + 6);
  generate_4 (big + 8);
  generate_5 (big + 10);
  generate_6 (big + 12);
  generate_7 (big + 14);
  generate_8 (big + 16);
  generate_9 (big + 18);
  generate_a (big + 20);
  generate_b (big + 22);
  generate_c (big + 24);
  generate_d (big + 26);
  generate_e (big + 28);
  generate_f (big + 30);
  generate_plus (big + 32);
  generate_minus (big + 34);
  fwrite (big, 36, sizeof (int), file);

  return 0;
}