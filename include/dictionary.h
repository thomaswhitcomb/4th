#ifndef _dictionary_h_
#define _dictionary_h_

#include "common.h"

typedef struct {
  char *verb;
  word_t *words;
} dict_entry;

void add_dictionary_entry();
void search_dictionary();

#endif
