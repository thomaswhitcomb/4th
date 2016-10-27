#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "dictionary.h"
#include "stack.h"
#include "heap.h"
#include "compile.h"
#include "execute.h"
#include "run.h"

#define MAX_WORDS_IN_DEFINE 50

static int state = STATE_EXECUTE;
static int verb_needed;
static int compiled_top;
static char* verb;
static word_t *compiled = NULL;

int get_state(){
  return state;
}
void set_state(int s){
  state = s;
}

void define_end(){
  word_t word;
  set_state(STATE_EXECUTE);

  word.ptr = compiled;
  stack_push(&data_stack,word);

  word.char_ptr = verb;
  stack_push(&data_stack,word);

  add_dictionary_entry();
}

void define(){
  set_state(STATE_COMPILE);
  compiled_top = 0;
  compiled = heap_get_words(MAX_WORDS_IN_DEFINE);
  verb_needed = 1;
}

void run(){
  word_t word;

  word = stack_pop(&data_stack);
  char *token = word.char_ptr;

  if(!token){
    bye();
  }
  if(get_state() == STATE_EXECUTE){
    word_t word;

    word.char_ptr = token;
    stack_push(&data_stack,word);
    compile();
    word.ptr = stack_pop(&data_stack).ptr;

    stack_push(&data_stack,word);
    execute();

  } else {
    if(verb_needed){
      verb = (char *)heap_get(strlen(token)+1);
      strcpy(verb,token);
      verb_needed = 0;
    }
    else{

      if(!strcmp(token,"if")){
        word_t word;
        compiled[compiled_top++].number = COND_BRANCH;
        word.ptr = compiled+compiled_top;
        stack_push(&data_stack,word);
        compiled_top++;  // step past word for relative branch
      } else if(!strcmp(token,"do")){
        word_t word;
        compiled[compiled_top++].number = COND_BRANCH;
        word.ptr = compiled+compiled_top;
        stack_push(&data_stack,word);
        compiled_top++;  // step past word for relative branch
      } else if(!strcmp(token,"then")){
        word_t word = stack_pop(&data_stack);
        word_t relative;
        relative.ptr = (union word_t_union *) (compiled+compiled_top-word.ptr);
        (*word.ptr).number = relative.number;
      } else if(!strcmp(token,"else")){
        word_t if_loc = stack_pop(&data_stack);  // get the if locationa

        word_t word;
        compiled[compiled_top++].number = UNCOND_BRANCH; // add uncondition branch to then
        word.ptr = compiled+compiled_top;
        stack_push(&data_stack,word);
        compiled_top++;  // step past word for relative branch

        word_t relative;
        relative.ptr = (union word_t_union *) (compiled+compiled_top-if_loc.ptr);
        (*if_loc.ptr).number = relative.number;

      } else if(!strcmp(token,"begin")){
        word_t word;
        word.number = compiled_top;
        stack_push(&data_stack,word); 
      } else if(!strcmp(token,"until")){
        word_t begin_loc = stack_pop(&data_stack);  // get the begin locationa
        compiled[compiled_top++].number = COND_BRANCH;
        compiled[compiled_top].number = 0-(compiled_top-begin_loc.number);
        compiled_top++;
      } else if(!strcmp(token,";")){
        word_t word;

        word.char_ptr = token;
        stack_push(&data_stack,word);
        compile();
        word.ptr = stack_pop(&data_stack).ptr;

        stack_push(&data_stack,word);
        execute();

      } else {
        word_t word;
        word.char_ptr = token;
        stack_push(&data_stack,word);
        compile();
        word_t words;
        words.ptr = stack_pop(&data_stack).ptr;
        while((*words.ptr).number != 0){
          compiled[compiled_top++] = *words.ptr;
          words.ptr++;
          compiled[compiled_top++] = *words.ptr;
          words.ptr++;
        }
      }
      if(compiled_top > MAX_WORDS_IN_DEFINE){
        fprintf(stderr, "\r\nMax compose exceeded\n");
        bye();
      }
    }
  }
}
