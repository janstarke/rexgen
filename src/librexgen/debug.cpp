#include "debug.h"

static int level = 0;
static char space_buffer[512];

void enter_level() { ++level; }
void leave_level() { --level; }

int get_level() { return level; }

char* spaces(char c, int s) {
  if (((size_t)s) > (sizeof(space_buffer)/sizeof(space_buffer[0])-1)) {
    return NULL;
  }
  for (int n=0; n<s; ++n) {
    space_buffer[n] = c;
  }
  space_buffer[s] = '\0';
  return space_buffer;
}