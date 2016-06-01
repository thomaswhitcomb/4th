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
//  word_t *loc;
//  loc = words;
//  printf(" - ");
//  while((*loc).number){
//    printf("%ld ",(*loc).number);
//    loc++;
//  }
//  printf("will execute ");
  while((*words).number){
    switch((*words).number) {
      case LITERAL :
        words++;
        stack_push(*words);
        words++;
        break;
      case COND_BRANCH :
        words++; //step past the literal
        word_t w = stack_pop();
        if(w.number == 0) words = words + ((*words).number);
        else words++;
        break;
      case UNCOND_BRANCH :
        words++; //step past the literal
        words = words + ((*words).number);
        break;
      case RUN_NATIVE :
        words++;
        (*words).code();
        words++;
        break;
      case RUN_COMPOSED :
        words++;
        execute(words->ptr);
        words++;
        break;
      default :  
        printf("execute - dont recognize %ld\n",((*words).number));
        words++;
    }
  }
}

int main(){
  word_t *words;
  char *token;
  printf("word_t size is %lu\n",sizeof(word_t));
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
