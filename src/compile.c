#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stack.h>
#include "common.h"
#include "dictionary.h"
#include "io.h"
#include "heap.h"
#include "execute.h"
#include "compile.h"

static word_t compiled[3];
static int compiled_top = 0;

static int all_digits(char *token){
  while(*token){
    if(!isdigit(*token)) return 0;
    token++;
  }
  return 1;
}

word_t *compile(char *token){
  word_t *existing_words;
  compiled_top = 0;
  if((existing_words = search_dictionary(token)) != NULL){
    compiled[compiled_top++].run = execute;
    compiled[compiled_top++].ptr = existing_words;
  } else if(all_digits(token)){
    word_t si;
    si.number = atoi(token);
    compiled[compiled_top++].run = push_literal;
    compiled[compiled_top++].number = si.number;
  } else{
    printf(" compile problem ");
  }
  compiled[compiled_top++].number = 0;
  return compiled;
}
