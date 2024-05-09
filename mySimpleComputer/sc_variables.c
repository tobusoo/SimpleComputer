#include "sc_variables.h"

CacheLine cache[5];
bool sc_cache_ignore = 0;
int sc_memory[SC_MEMORY_SIZE];
int sc_idle_clock;
int sc_accumulator;
int sc_command_counter;
int sc_register;