#pragma once
#include "myTerm.h"

void printCell (int address, enum colors fg, enum colors bg);
void printFlags (void);
void printDecodedCommand (int value);
void printAccumulator (void);
void printCounters (void);
void printCommand (void);
void printMemory (void);
void printTerm (int address, int input);
void printCache ();
void updateTerm ();

void CU ();
int ALU (int command, int operand);
void IRC (int signum);