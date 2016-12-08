#ifndef _common_h_
#define _common_h_

#define DEBUG 1
#undef DEBUG

#define COND_BRANCH 2L
#define UNCOND_BRANCH 3L
#define RUN_NATIVE 4L

#define MAX_TOKEN_SIZE 15
#define MAX_LINE_SIZE 255

extern void bye();

typedef void (*native_sig)();

typedef union word_t_union {
  long number;
  union word_t_union *ptr;
  native_sig code;
  char *char_ptr;
} word_t;

#endif
