#include <stdbool.h>

#include <mySimpleComputer.h>

static int
complement_code (int x)
{
  bool sign = x >> 14;
  if (sign == 0)
    return x;

  x = ((~x + 1) | 0b1 << 14) & 0b111111111111111;
  return x == 0b100000000000000 ? 0 : x;
}

int
DIV (int x, int y)
{
  int div;
  bool x_sign = x >> 14;
  bool y_sign = y >> 14;

  x <<= 17;
  y <<= 17;

  div = (x / y) & 0b111111111111111;
  div = x_sign ^ y_sign ? div | (0b1 << 14) : div;

  return div;
}

int
MULT (int x, int y)
{
  int mult = 0;
  bool x_sign = x >> 14;
  bool y_sign = y >> 14;

  for (int i = 0; i < 13; i++)
    {
      mult += (x << i) * SC_BIT_GET (y, i + 1);
    }

  mult = x_sign ^ y_sign ? mult | (0b1 << 14) : mult;
  return mult & 0b111111111111111;
}

int
ALU (int command, int operand)
{
  int value, accum, comp_value, comp_accum;
  sc_memoryGet (operand, &value);
  comp_value = complement_code (value);
  sc_accumulatorGet (&accum);
  comp_accum = complement_code (accum);

  switch (command)
    {
    case 0x1E: // ADD
      sc_accumulatorSet ((comp_accum + comp_value) & 0b111111111111111);
      break;
    case 0x1F: // SUB
      if (value >> 14)
        SC_BIT_RM (value, 15);
      else
        SC_BIT_SET (value, 15);
      comp_value = complement_code (value);

      sc_accumulatorSet ((comp_accum + comp_value) & 0b111111111111111);
      break;
    case 0x20: // DIVIDE
      if (value == 0)
        {
          sc_regSet (SC_DIV_BY_ZERO, 1);
          return -1;
        }
      sc_regSet (SC_DIV_BY_ZERO, 0);
      sc_accumulatorSet (complement_code (DIV (accum, value)));
      break;
    case 0x21: // MUL
      sc_accumulatorSet (complement_code (MULT (accum, value)));
      break;
    case 0x33: // NOT
      sc_memorySet (value, ~accum & 0b111111111111111);
      break;
    case 0x34: // AND
      sc_accumulatorSet (accum & value);
      break;
    case 0x35: // OR
      sc_accumulatorSet (accum | value);
      break;
    case 0x36: // XOR
      sc_accumulatorSet (accum ^ value);
      break;
    default: // INVALID COMMAND
      sc_regSet (SC_INVALID_COMMAND, 1);
      return -1;
    }

  sc_regSet (SC_INVALID_COMMAND, 0);
  return 0;
}