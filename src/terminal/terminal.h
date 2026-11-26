#ifndef TERMINAL_H
#define TERMINAL_H

#include <termios.h>

struct editorConfig {
  int screenrows;
  int screencolumns;
  struct termios orig_termios;
};

extern struct editorConfig E;

void die(const char *s);

void initEditor();

void disableRawMode();

void enableRawMode();

#endif // !TERMINAL_H
