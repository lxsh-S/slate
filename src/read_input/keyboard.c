#include "../terminal/terminal.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef CTRL_KEY
#define CTRL_KEY(k) ((k) & 0x1f)
#endif

char editorReadKey() {
  int nread;
  char c;

  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    if (nread == -1 && errno != EAGAIN)
      die("read");
  }

  return c;
}

void editorProcessKeypress() {
  char c = editorReadKey();

  switch (c) {
  case CTRL_KEY('q'):
    exit(0);
    break;
  }
}
