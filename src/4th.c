#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "dictionary.h"
#include "stack.h"
#include "builtins.h"
#include "compile.h"
#include "io.h"

int state;
void execute(word_t *words,int count);

void execute(word_t *words,int count){
  word_t *end;
  end = words + count;
  while(words < end){
    if((*words).number == LITERAL){
      words++;
      stack_push(*words);
      words++;
    }else if ((*words).number == COND_BRANCH) {
      words++; //step past the literal
      word_t w = stack_pop();
      if(w.number == 0) words = words + ((*words).number);
      else words++;
    }else if ((*words).number == UNCOND_BRANCH) {
      words++; //step past the literal
      words = words + ((*words).number);
    }else {
      (*words).code();
      words++;
    }
  }
}

int main(){
  word_t *words;
  char *token;
  int count;
  printf("word_t size is %lu\n",sizeof(word_t));
  printf("word_struct_t size is %lu\n",sizeof(word_struct_t));
  set_raw_tty();
  builtins_init();
  state = STATE_EXECUTE;
  while(1){
    token = io_get_token();
    if(!token){
      bye();
    }
    words = compile(token,&count);
    execute(words,count);
  }
}
