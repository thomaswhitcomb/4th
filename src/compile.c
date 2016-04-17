#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stack.h>
#include "dictionary.h"
#include "io.h"
#include "compile.h"

static word_t compiled[25];
static int compiled_top = 0;

static int all_digits(char *token){
  while(*token){
    if(!isdigit(*token)) return 0;
    token++;
  }
  return 1;
}

word_t *compile(char *token, int *count){
  word_t *existing_words;
  dict_block *block;
  compiled_top = 0;

  if(token == NULL){
    *count = 0;
    return compiled;
  }
  if((block = search_dictionary(token)) != NULL){
    existing_words = block->words;
    for(int i=0;i<block->count;i++){
      compiled[compiled_top++] = *existing_words;
      existing_words++;
    }
  } else if(all_digits(token)){
    word_t si;
    si.number = atoi(token);
    compiled[compiled_top++] = (word_t)LITERAL; // literal
    compiled[compiled_top++] = si;
  } else{
    puts("crap error");
  }
  *count = compiled_top;
  return compiled;
}
