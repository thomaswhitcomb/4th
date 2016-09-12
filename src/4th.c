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

void run_line(char *);
int load_composed();
void read();

char boot[] = {": boot begin read run 0 until ;"};
char *boot_word = "boot";

int main(){
  printf("word_t size is %lu. begin...\n",sizeof(word_t));

  builtins_init();
  run_line(boot);
  if(load_composed()){
    puts("Cannot open 4th.conf");
    bye();
  }

  set_raw_tty();

  word_t word;
  word.char_ptr = boot_word;
  stack_push(&data_stack,word);
  compile();
  word.ptr = stack_pop(&data_stack).ptr;

  stack_push(&data_stack,word);
  execute();
}

int load_composed(){
  FILE * fp;
  char line[255];
  size_t len = 0;
  ssize_t read;
  int ch;
  int loc = 0;

  fp = fopen("4th.conf", "r");
  if (fp == NULL)
    return 1;

  while ((ch = getc(fp)) != EOF) {
    if(ch != '\n'){
      line[loc++] = ch;
    } else{
      line[loc++] = '\0';
      run_line(line);
      loc = 0;
    }
  }

  fclose(fp);

  return 0;
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
