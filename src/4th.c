#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "dictionary.h"
#include "stack.h"
#include "heap.h"
#include "builtins.h"
#include "compile.h"
#include "execute.h"
#include "io.h"

#define MAX_WORDS_IN_DEFINE 50
int state;
int verb_needed;
int compiled_top;
char* verb;
word_t *compiled = NULL;

void define_end(){
  state = STATE_EXECUTE;
  add_dictionary_entry(verb,compiled);
}
void define(){
  state = STATE_COMPILE;
  compiled_top = 0;
  compiled = heap_get_words(MAX_WORDS_IN_DEFINE);
  verb_needed = 1;
}

int main(){
  char *token;
  printf("word_t size is %lu\n",sizeof(word_t));
  set_raw_tty();

  builtins_init();
  define_builtin(":",define);
  define_builtin(";",define_end);

  state = STATE_EXECUTE;
  while(1){
    token = io_get_token();
    if(!token){
      bye();
    }
    if(state == STATE_EXECUTE){
      word_t word;
      word.ptr = compile(token);
      execute(word);
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
          stack_push(word);
          compiled_top++;  // step past word for relative branch
        } else if(!strcmp(token,"then")){
          word_t word = stack_pop();
          word_t relative;
          relative.ptr = (union word_t_union *) (compiled+compiled_top-word.ptr);
          (*word.ptr).number = relative.number;
        } else if(!strcmp(token,"else")){
          word_t if_loc = stack_pop();  // get the if locationa

          word_t word;
          compiled[compiled_top++].number = UNCOND_BRANCH; // add uncondition branch to then
          word.ptr = compiled+compiled_top;
          stack_push(word);
          compiled_top++;  // step past word for relative branch

          word_t relative;
          relative.ptr = (union word_t_union *) (compiled+compiled_top-if_loc.ptr);
          (*if_loc.ptr).number = relative.number;

        } else if(!strcmp(token,";")){
          word_t word;
          word.ptr = compile(token);
          execute(word);
        } else {
          word_t *words = compile(token);
          while((*words).number != 0){
            compiled[compiled_top++] = *words;
            words++;
            compiled[compiled_top++] = *words;
            words++;
          }
        }
        if(compiled_top > MAX_WORDS_IN_DEFINE){
          fprintf(stderr, "\r\nMax compose exceeded\n");
          bye();
        }
      }
    }
  }
}
