#ifndef _dictionary_h_
#define _dictionary_h_

#include "common.h"

typedef struct {
  char *verb;
  word_t *words;
} dict_entry;

void add_dictionary_entry(char *verb,word_t *words);
word_t *search_dictionary(char *verb);

#endif
