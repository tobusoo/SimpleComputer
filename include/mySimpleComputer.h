#pragma once

#define SC_OVERFLOW 1
#define SC_DIV_BY_ZERO 2
#define SC_OUT_OF_RANGE 3
#define SC_IGNORE_CLOCK_PULSE 4
#define SC_INVALID_COMMAND 5
#define SC_REG_FLAGS_N 5

#define SC_BIT_SET(REGISTER, BIT_N) REGISTER = REGISTER | (1 << (BIT_N - 1))
#define SC_BIT_RM(REGISTER, BIT_N) REGISTER = REGISTER & (~(1 << (BIT_N - 1)))
#define SC_BIT_GET(REGISTER, BIT_N) (REGISTER >> (BIT_N - 1) & 0x1)

int sc_memoryInit (void);
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int *value);
int sc_memoryLoad (char *filename);
int sc_memorySave (char *filename);

int sc_regInit (void);
int sc_regSet (int registr, int value);
int sc_regGet (int registr, int *value);

int sc_accumulatorInit (void);
int sc_accumulatorSet (int value);
int sc_accumulatorGet (int *value);

int sc_icounterInit (void);
int sc_icounterSet (int value);
int sc_icounterGet (int *value);

int sc_commandEncode (int sign, int command, int operand, int *value);
int sc_commandDecode (int value, int *sign, int *command, int *operand);
int sc_commandValidate (int command);
