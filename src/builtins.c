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

#define MAX_WORDS_IN_DEFINE 50

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
  words[0].run = stack_push;
  words[1].ptr = heap_get_words(1);
  words[2].number = 0;
  add_dictionary_entry(var,words);
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
void define_builtin(char *verb,native_sig code){
  word_t *words = heap_get_words(3);
  words[0].run = run_native;
  words[1].code = code;
  words[2].number = 0;
  add_dictionary_entry(verb,words);
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
  define_builtin("inc",inc);
  define_builtin("dec",dec);
  define_builtin("bye",bye);
  define_builtin(".",dot);
}
