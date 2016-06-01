#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "dictionary.h"
#include "stack.h"
#include "builtins.h"
#include "compile.h"
#include "execute.h"
#include "io.h"

int state;

int main(){
  word_t *words;
  word_t word;
  char *token;
  printf("word_t size is %lu\n",sizeof(word_t));
  set_raw_tty();
  builtins_init();
  state = STATE_EXECUTE;
  while(1){
    token = io_get_token();
    if(!token){
      bye();
    }
    word.ptr = compile(token);
    execute(word);
  }
}
