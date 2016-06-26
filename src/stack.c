#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "stack.h"

void stack_push(stack_tt *stack,word_t item){
  stack->top ++;
  if(stack->top >= STACK_SIZE){
    fprintf(stderr, "Stack full. %d elements\n",stack->top);
    exit(EXIT_FAILURE);
  }
  stack->stack[stack->top] = item;
}
word_t stack_pop(stack_tt *stack){
  word_t si  = stack->stack[stack->top];
  stack->top--;
  return si;
}

void stack_print(stack_tt *stack){
  printf(" <%d>",(stack->top)+1);
  for(int i=0;i<=stack->top;i++){
    printf(" %lu",stack->stack[i].number);
  }
}
