#include "termios.h"
#include "unistd.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

struct termios orig_termios;

void die(const char *s) {
  perror(s);
  exit(1);
}

void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    die("tcseattr");
}

void enableRawMode() {

  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
    die("tcgetattr");

  // we gonna use at-exit so that it
  // disables raw mode at exit
  atexit(disableRawMode);

  struct termios raw = orig_termios;

  raw.c_iflag &= ~(ICRNL | IXON | ISTRIP | BRKINT | INPCK);

  raw.c_oflag &= ~(OPOST);

  raw.c_cflag |= (CS8);

  raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);

  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
    die("tcsetattr");
}

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
    if (c == 'q')
      break;
  }

  return 0;
}
