#pragma once
#include <stdbool.h>

#define SC_MEMORY_SIZE 128
extern int sc_memory[SC_MEMORY_SIZE];

#define CACHE_LINES 5
#define CACHE_LINE_SIZE 10

typedef struct CacheLine
{
  int values[CACHE_LINE_SIZE];
  int number;
  int priority;
  bool use;
} CacheLine;

extern CacheLine cache[CACHE_LINES];
extern bool sc_cache_ignore;

extern int sc_idle_clock;
extern int sc_accumulator;
extern int sc_command_counter;
extern int sc_register;