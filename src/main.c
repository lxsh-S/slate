#include "termios.h"
#include "unistd.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

struct termios orig_termios;

void disableRawMode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); }

void enableRawMode() {

  tcgetattr(STDIN_FILENO, &orig_termios);
  // we gonna use at-exit so that it
  // disables raw mode at exit
  atexit(disableRawMode);

  struct termios raw = orig_termios;

  // les also turn of conanical mode
  // so that we can read output in conanical
  // mode :)
  raw.c_lflag &= ~(ECHO | ICANON | ISIG);

  raw.c_lflag &= ~(ECHO);

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {

  // enable the raw mode
  enableRawMode();

  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
    if (iscntrl(c)) {
      printf("%d\n", c);
    } else {
      printf("%d ('%c')\n", c, c);
    }
  };
  return 0;
}
