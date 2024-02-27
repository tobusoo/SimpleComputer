#pragma once
#include "myTerm.h"

void printBox (int row, int col, int w, int h, char *title);
void printCell (int address, enum colors fg, enum colors bg);
void printFlags (void);
void printDecodedCommand (int value);
void printAccumulator (void);
void printCounters (void);
void printCommand (void);
void printTerm (int address, int input);