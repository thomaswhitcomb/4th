#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "stack.h"
#include "builtins.h"
#include "compile.h"
#include "run.h"
#include "execute.h"
#include "io.h"

stack_tt data_stack = {.top = -1};
stack_tt return_stack = {.top = -1};

char composed[][80] = {
   {": rot3 rot rot rot ;"}
  ,{": +! dup @ rot + swap ! ;"}
  ,{": inc 1 + ;"}
  ,{": dec 1 - ;"}
  ,{": quadratic >r swap rot r@ * + r> * + ;"}
  ,{": boot begin read run 0 until ;"}
  ,{0}
};
void run_line(char *);
void load_composed();
void read();

int main(){
  printf("word_t size is %lu\n",sizeof(word_t));

  builtins_init();
  load_composed();

  set_raw_tty();

  word_t word;
  word.char_ptr = "boot";
  stack_push(&data_stack,word);
  compile();
  word.ptr = stack_pop(&data_stack).ptr;

  stack_push(&data_stack,word);
  execute();
}

void load_composed(){
  int i = 0;
  while(composed[i][0] != 0){
    run_line(composed[i]);
    i=i+1;
  }
}

void run_line(char *line){
  word_t word;
  char *token;
  token = strtok(line," ");
  do{
    word.char_ptr = token;
    stack_push(&data_stack,word);
    run();
  } while ((token = strtok(NULL," ")) != NULL);
}
