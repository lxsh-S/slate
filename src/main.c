#include "terminal.h"

#include "unistd.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>

#define CTRL_KEY(k) ((k) & 0x1f)

int main() {

  // enable the raw mode
  enableRawMode();

  while (1) {
    char c = '\0';
    if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
      die("read");

    if (iscntrl(c)) {
      printf("%d\r\n", c);
    } else {
      printf("%d ('%c')\r\n", c, c);
    }
    if (c == CTRL_KEY('q'))
      break;
  }

  return 0;
}
