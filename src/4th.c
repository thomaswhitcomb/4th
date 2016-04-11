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
void execute(word_t *words);

void execute(word_t *words){
  while((*words).number != 0){
    if((*words).number == LITERAL){
      words++;
      stack_push(*words);
      words++;
    }else if ((*words).number == COND_IF) {
      words++; //step past the if
      word_t w = stack_pop();
      if(w.number == 0) words = words + ((*words).number);
      else words++;
    }else {
      (*words).code();
      words++;
    }
  }
}

int main(){
  word_t *words;
  char *token;
  //fprintf(stderr,"Type `bye` - to exit.");
  set_raw_tty();
  builtins_init();
  state = STATE_EXECUTE;
  while(1){
    token = io_get_token();
    if(!token){
      bye();
    }
    words = compile(token);
    execute(words);
  }
}
