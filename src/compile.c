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

word_t *compile(char *token){
  word_t *existing_words;
  compiled_top = 0;

  if(token == NULL){
    compiled[compiled_top++].number = 0;
    return compiled;
  }
  if((existing_words = search_dictionary(token)) != NULL){
    while((*existing_words).number){
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

  compiled[compiled_top++].number = 0;
  return compiled;
}
