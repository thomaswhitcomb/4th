#include <stdio.h>
#include <stdlib.h>
#include "common.h"

#define WORD_HEAP_SIZE 300
#define BYTE_HEAP_SIZE 1024

static word_t word_heap[WORD_HEAP_SIZE];
static int top_words = 0;

static void* byte_heap[BYTE_HEAP_SIZE];
static int top = 0;

word_t *heap_get_words(int count){
  if(top_words >= WORD_HEAP_SIZE ) {
    fprintf(stderr, "\r\nWord HEAP empty. %d words\n",top_words);
    bye();
  }
  word_t *ptr = &word_heap[top_words];
  top_words = top_words + count;
  return ptr;
}

void *heap_get(int count){
  if(top_words >= BYTE_HEAP_SIZE) {
    fprintf(stderr, "\r\nByte HEAP empty\n");
    bye();
  }
  void *ptr = &byte_heap[top];
  top = top + count;
  return ptr;
}
