#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "stack.h"

#define STACK_SIZE 50
static word_t stack[STACK_SIZE];
static int top = -1;

void stack_push(word_t item){
  top ++;
  if(top >= STACK_SIZE){
    fprintf(stderr, "Stack full. %d elements\n",top);
    exit(EXIT_FAILURE);
  }
  stack[top] = item;
}
word_t stack_pop(){
  word_t si  = stack[top];
  top--;
  return si;
}

void stack_dot_s(){
  printf(" <%d>",top+1);
  for(int i=0;i<=top;i++){
    printf(" %lu",stack[i].number);
  }
}
