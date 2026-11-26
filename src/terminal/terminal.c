#include "terminal.h"
#include "../read_input/keyboard.h"
#include "termios.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

struct editorConfig E;

int getCursorPosition(int *rows, int *cols) {

  char buf[32];
  unsigned int i = 0;

  if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4)
    return -1;

  while (i < sizeof(buf) - 1) {
    if (read(STDIN_FILENO, &buf[i], 1) != 1)
      break;

    // we read till R char
    if (buf[i] == 'R')
      break;
    i++;
  }

  // assign to final byte of
  // array
  buf[i] = '\0';

  // parse
  // make sure tht it responded
  // with escape sequenc
  if (buf[0] != '\x1b' || buf[1] != '[')
    return -1;
  if (sscanf(&buf[2], "%d;%d", rows, cols) != 2)
    return -1;

  return 0;

  printf("\r\n&buf[1]: '%s'\r\n", &buf[1]);

  printf("\r\n");

  char c;

  while (read(STDIN_FILENO, &c, 1) == 1) {
    if (iscntrl(c)) {
      printf("%d\r\n", c);
    } else {
      printf("%d ('%c')\r\n", c, c);
    }
  }

  editorReadKey();

  return -1;
}

int getWindowSize(int *rows, int *cols) {
  struct winsize ws;

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
    // fallback method for getting screensize
    // using a very big value so tht we forsure
    // reach the bottom right
    if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12)
      return getCursorPosition(rows, cols);
  } else {
    *cols = ws.ws_col;
    *rows = ws.ws_row;
    return 0; // no error got the terminal screen size
  }
  return 0;
}

void die(const char *s) {
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);

  perror(s);
  exit(1);
}

void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1)
    die("tcsetattr");
}

void enableRawMode() {
  if (tcgetattr(STDIN_FILENO, &E.orig_termios) == -1)
    die("tcgetattr");

  atexit(disableRawMode);

  struct termios raw = E.orig_termios;

  raw.c_iflag &= ~(ICRNL | IXON | ISTRIP | BRKINT | INPCK);

  raw.c_oflag &= ~(OPOST);

  raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);

  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
    die("tcsetattr");
}

void initEditor() {
  if (getWindowSize(&E.screenrows, &E.screencolumns) == -1)
    die("getWindowSize");
}
