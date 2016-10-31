#include <stdio.h>
#include <state.h>
static int state = STATE_EXECUTE;

int get_state(){
  return state;
}
void set_state(int s){
  state = s;
}
