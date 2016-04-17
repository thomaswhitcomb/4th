#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "heap.h"
#include "dictionary.h"

static dict_entry dictionary[100];
static int dictionary_size = 0;

dict_block *search_dictionary(char *verb){
  for(int i=0;i<dictionary_size;i++){
    if(!strcmp(verb,dictionary[i].verb)){
      return &dictionary[i].block;
    }
  }
  return NULL;
}

void add_dictionary_entry(char *verb,int count, word_t *words){
  int l = strlen(verb);
  char* chars = (char *)heap_get(l+1);
  strcpy(chars,verb);
  dictionary[dictionary_size].verb = chars;
  dictionary[dictionary_size].block.count = count;
  dictionary[dictionary_size].block.words = words;
  dictionary_size++;
}
