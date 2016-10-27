#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "string.h"
#include "ctype.h"
#include "common.h"
#include "run.h"
#include "io.h"

static int raw_mode = 0;
static char *token_ptr = NULL;
static char stmt[MAX_LINE_SIZE];
static char token[MAX_TOKEN_SIZE];
static int last_char = 0;
struct termios initial_ios,raw_ios;

void bye(){
  if(raw_mode){
    int i = tcsetattr(STDIN_FILENO,TCSAFLUSH,&initial_ios);
    puts("");
  }
  exit(EXIT_SUCCESS);
}

void set_raw_tty(){
  int i = tcgetattr(STDIN_FILENO,&initial_ios);
  if(i != 0){
    raw_mode = 0;
    return;
  }
  raw_mode = 1;

  raw_ios = initial_ios;

  raw_ios.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw_ios.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw_ios.c_cflag &= ~(CSIZE | PARENB);
  raw_ios.c_cflag |= CS8;
  raw_ios.c_oflag &= ~(OPOST);
  raw_ios.c_cc[VMIN] = 1;
  raw_ios.c_cc[VTIME] = 0;

  i = tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw_ios);
  if(i != 0){
    printf("tcsetattr failed: %d\n",i);
  }
}
static int pos = -1;
static char *bufr;
char * io_get_token(){
  int e;
  if(pos == -1){
    do {
      bufr = io_get_line();
      if(bufr == NULL) return NULL;
      // remove trailing spaces
      e = strlen(bufr) - 1;
      while(e >= 0 && isspace(bufr[e])) e--;
    } while(e == -1);
    bufr[e+1] = '\0';
    pos = 0;
  }

  while(isspace(bufr[pos])) pos++;

  int i = 0;
  while(bufr[pos] > 32){
    if(i >= MAX_TOKEN_SIZE - 1){
      printf("\r\nMaximum token size exceeded");
      bye();
    }
    token[i++] = bufr[pos++];
  }
  token[i] = '\0';

  if(bufr[pos] == '\0') pos = -1;

  return token;
}

char * io_get_line(){
  int i = 0, c;
  if(last_char == 13 || last_char == 10){
    if(get_state() == STATE_EXECUTE) puts(" ok");
    else if(get_state() == STATE_COMPILE) puts(" compiled");
    else puts(" whoops bad state");
    putchar('\r');
  }
  if(feof(stdin)) return NULL;
  last_char = 0;
  while((c = getchar()) !=EOF) {

    if(i >= MAX_LINE_SIZE){
      printf("\r\nMaximum line size exceeded");
      bye();
    }

    if(c == 10 || c == 13) {
      stmt[i++] = '\0';
      last_char = c;
      return stmt;
    }
    if(c == 127){
      if(i>0){
        i--;
        printf("\b");
      }
    } else{
      stmt[i++] = c;
      if(raw_mode){
         putchar(c);
      }
    }
  }
  return NULL;
}
