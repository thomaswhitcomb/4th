#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "common.h"
#include "dictionary.h"
#include "stack.h"
#include "builtins.h"
#include "heap.h"
#include "compile.h"
#include "io.h"

void define_end(){
  state = STATE_EXECUTE;
}
void define(){
  char *token;

  state = STATE_COMPILE;

  word_t *compiled = heap_get_words(25);
  int compiled_top = 0;
  word_t *words;
  char *s = io_get_token();
  int l = strlen(s);
  char* verb = (char *)heap_get(l+1);
  strcpy(verb,s);
  do{
    token = io_get_token();
    if(!strcmp(token,"if")){
      word_t word;
      compiled[compiled_top++] = (word_t)COND_BRANCH;
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
      compiled[compiled_top++] = (word_t)UNCOND_BRANCH; // add uncondition branch to then
      word.ptr = compiled+compiled_top;
      stack_push(word);
      compiled_top++;  // step past word for relative branch

      word_t relative;
      relative.ptr = (union word_t_union *) (compiled+compiled_top-if_loc.ptr);
      (*if_loc.ptr).number = relative.number;

    } else {
      int count;
      words = compile(token,&count);
      for(int i=0;i<count;i++){
        compiled[compiled_top++] = *words;
        words++;
      }
    }
  } while(strcmp(token,";") != 0);
  add_dictionary_entry(verb,compiled_top,compiled);

}
void dot(){
  word_t x = stack_pop();
  printf(" %lu",x.number);
}

void drop(){
  stack_pop();
}
void dup(){
  word_t x = stack_pop();
  stack_push(x);
  stack_push(x);
}
void plus(){
  word_t x = stack_pop();
  word_t y = stack_pop();
  word_t si;
  si.number = x.number + y.number;
  stack_push(si);
}
void minus(){
  word_t x = stack_pop();
  word_t y = stack_pop();
  word_t si;
  si.number = y.number - x.number;
  stack_push(si);
}
void times(){
  word_t x = stack_pop();
  word_t y = stack_pop();
  word_t si;
  si.number = y.number * x.number;
  stack_push(si);
}
void modulo(){
  word_t x = stack_pop();
  word_t y = stack_pop();
  word_t si;
  si.number = y.number % x.number;
  stack_push(si);
}
void swap(){
  word_t x = stack_pop();
  word_t y = stack_pop();
  stack_push(x);
  stack_push(y);
}

void over(){
  word_t x = stack_pop();
  word_t y = stack_pop();
  stack_push(y);
  stack_push(x);
  stack_push(y);
}

void rot(){
  word_t x = stack_pop();
  word_t y = stack_pop();
  word_t z = stack_pop();
  stack_push(y);
  stack_push(x);
  stack_push(z);
}
void minus_rot(){
  word_t x = stack_pop();
  word_t y = stack_pop();
  word_t z = stack_pop();
  stack_push(x);
  stack_push(z);
  stack_push(y);
}

void variable(){
  char *var = io_get_token();
  word_t *words = heap_get_words(3);
  words[0].number = LITERAL;
  words[1].ptr = heap_get_words(1);
  add_dictionary_entry(var,2,words);
}

void put(){
  word_t loc = stack_pop();
  word_t value = stack_pop();
  ((word_t *)loc.ptr)->number = value.number;
}

void get(){
  word_t addr = stack_pop();
  word_t w = *(word_t *)(addr.ptr);
  stack_push(w);
}

void inc() {
  word_t value = stack_pop();
  value.number = value.number + 1;
  stack_push(value);
}
void dec() {
  word_t value = stack_pop();
  value.number = value.number - 1;
  stack_push(value);
}

  //"-rot",{(word_t) rot, (word_t) rot, 0},
  //"nip",{(word_t) swap, (word_t) drop, 0},
  //"tuck",{(word_t) swap, (word_t) over, 0},
void define_builtin(char *verb,verb_sig code){
  word_t *words = heap_get_words(1);
  words[0].code = code;
  add_dictionary_entry(verb,1,words);
}

void builtins_init(){
  define_builtin(".s",stack_dot_s);
  define_builtin("+",plus);
  define_builtin("*",times);
  define_builtin("-",minus);
  define_builtin("mod",modulo);
  define_builtin("drop",drop);
  define_builtin("dup",dup);
  define_builtin("swap",swap);
  define_builtin("over",over);
  define_builtin("rot",rot);
  define_builtin("variable",variable);
  define_builtin("!",put);
  define_builtin("@",get);
  define_builtin(":",define);
  define_builtin(";",define_end);
  define_builtin("inc",inc);
  define_builtin("dec",dec);
  define_builtin("bye",bye);
  define_builtin(".",dot);
}
