#ifndef _dictionary_h_
#define _dictionary_h_

#include "common.h"

typedef struct {
  int count;
  word_t *words;
} dict_block;

typedef struct {
  char *verb;
  dict_block block;
} dict_entry;

void add_dictionary_entry(char *verb,int count, word_t *words);
dict_block *search_dictionary(char *verb);

#endif
