#ifndef _compile_h_
#define _compile_h_
#include "common.h"

void run_native(word_t word_code_ptr);
word_t *compile(char *token);

#endif
