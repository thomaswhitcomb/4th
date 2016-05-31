#ifndef _common_h_
#define _common_h_

#define DEBUG 1
#undef DEBUG

#define STATE_EXECUTE 1
#define STATE_COMPILE 2

extern int state;

#define LITERAL 1L
#define COND_BRANCH 2L
#define UNCOND_BRANCH 3L
#define RUN_NATIVE 4L
#define RUN_COMPOSED 5L

#define MAX_TOKEN_SIZE 15
#define MAX_LINE_SIZE 72

extern void bye();

typedef void (*verb_sig)();
typedef union word_t_union {
  long number;
  union word_t_union *ptr;
  verb_sig code;
} word_t;

#endif
