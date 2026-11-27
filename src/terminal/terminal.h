#ifndef TERMINAL_H
#define TERMINAL_H

#include <termios.h>

#define _BSD_SOURCE
#define _GNU_SCOURCE

typedef struct erow {
  int size;
  char *chars;
} erow;

struct editorConfig {
  int cx, cy;
  int screenrows;
  int screencolumns;
  int numrows;
  erow row;

  struct termios orig_termios;
};

extern struct editorConfig E;

struct abuf {
  char *b;
  int len;
};

void abAppend(struct abuf *ab, const char *s, int len);

void abFree(struct abuf *ab);

// represents an emty buf
// acts as cunstructor for
// abuf
#define ABUF_INIT {NULL, 0}

void die(const char *s);

void initEditor();

void disableRawMode();

void enableRawMode();

#endif // !TERMINAL_H
