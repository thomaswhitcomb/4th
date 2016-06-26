#ifndef _stack_h_
#define _stack_h_

#include "common.h"

#define STACK_SIZE 10
typedef struct {
  int top;
  word_t stack[STACK_SIZE];
} stack_tt;

extern stack_tt data_stack;
extern stack_tt return_stack;

void stack_push(stack_tt *stack, word_t item);
word_t stack_pop(stack_tt *stack);
void stack_print(stack_tt *stack);

#endif
