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

int main(){
  printf("word_t size is %lu. begin...\n",sizeof(word_t));

  builtins_init();
  if(load_composed()){
    puts("Cannot open 4th.conf");
    bye();
  }

  set_raw_tty();

  word_t word;
  word.char_ptr = "boot";
  stack_push(&data_stack,word);
  compile();
  word.ptr = stack_pop(&data_stack).ptr;

  stack_push(&data_stack,word);
  execute();
}

int load_composed(){
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen("4th.conf", "r");
  if (fp == NULL)
    return 1;

  while ((read = getline(&line, &len, fp)) != -1) {
    // remove the newline
    for(int i=len;i>0;i--){
      if(line[i] == '\n'){
        line[i]='\0';
        break;
      }
    }
    run_line(line);
  }

  if (line)
    free(line);
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
