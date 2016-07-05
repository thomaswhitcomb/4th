#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "heap.h"
#include "dictionary.h"

unsigned int hash(char *str);
static dict_entry dictionary[100] = {[0 ... 99] = {.verb = NULL,. words = NULL}};
static int dictionary_size = 0;

word_t *search_dictionary(char *verb){
  int index = hash(verb) % 100;
  while(dictionary[index].verb != NULL && strcmp(dictionary[index].verb,verb)){
    index++;
    if(index == 100) index = 0;
  }
  return dictionary[index].words;
  //for(int i=0;i<dictionary_size;i++){
  //  if(!strcmp(verb,dictionary[i].verb)){
  //    return dictionary[i].words;
  //  }
  //}
  //return NULL;
}

void add_dictionary_entry(char *verb, word_t *words){
  printf("adding %s\n",verb);
  int l = strlen(verb);
  char* chars = (char *)heap_get(l+1);
  strcpy(chars,verb);
  int index = hash(verb) % 100;
  while(dictionary[index].verb != NULL && strcmp(dictionary[index].verb,verb) ){
    index++;
    if(index == 100) index = 0;
  }
  dictionary[index].verb = chars;
  dictionary[index].words = words;
}

unsigned int hash(char *str)
{
    unsigned int hash = 5381;
    int c;

    while (0 != (c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
