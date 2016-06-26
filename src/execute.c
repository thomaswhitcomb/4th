#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "stack.h"
#include "builtins.h"

void execute(word_t words);

void execute(word_t x){
  word_t *words = x.ptr;

#ifdef DEBUG
  word_t *loc = words;
  printf(" execute ");
  while((*loc).number){
    printf("%ld ",(*loc).number);
    loc++;
    printf("%ld ",(*loc).number);
    loc++;
  }
#endif

  while((*words).number){
    switch((*words).number) {
      case COND_BRANCH :
        words++; //step past the literal
        word_t w = stack_pop(&data_stack);
        if(w.number == 0) words = words + ((*words).number);
        else words++;
        break;
      case UNCOND_BRANCH :
        words++; //step past the literal
        words = words + ((*words).number);
        break;
      default :
        (*words).run(*(words+1));
        words = words + 2;
    }
  }
}
