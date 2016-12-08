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

void run_list(char *list[]);
int load_composed();
void read();

char *boot[] = {":", "boot", "begin", "read", "run", "0","until",";",NULL};
char *boot_word = "boot";

int main(){
  puts("loading composed words");

  builtins_init();
  run_list(boot);
  if(load_composed()){
    puts("Cannot open 4th.conf");
    bye();
  }

  printf("word_t size is %lu\n",sizeof(word_t));
  puts("ready (\033[1;32mbye\033[0m to exit)");
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
  char token[MAX_TOKEN_SIZE];
  size_t len = 0;
  size_t read;
  int ch;

  fp = fopen("4th.conf", "r");
  if (fp == NULL)
    return 1;

  word_t word;
  int loc = 0;
  while ((ch = getc(fp)) != EOF) {
    if(loc >= MAX_TOKEN_SIZE) {
      puts("MAX TOKEN SIZE exceeded");
      bye();
    }
    if(ch == '\n' || ch == ' ') {
      token[loc++] = '\0';
      if(loc >1){
        word.char_ptr = token;
        stack_push(&data_stack,word);
        run();
      }
      loc = 0;
    }
    else token[loc++] = ch;
  }

  fclose(fp);

  return 0;
}

void run_list(char *list[]){
  word_t word;
  for(int i=0;list[i] != NULL;i++){
    word.char_ptr = list[i];
    stack_push(&data_stack,word);
    run();
  } 
}
