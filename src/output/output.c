#include "output.h"
#include "../terminal/terminal.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// VERSION
#define SLATE_VERSION "0.0.1<alpha>"

void editorScroll() {

  E.rx = 0;

  if (E.cy < E.numrows) {
    E.rx = editorRowCxToRx(&E.row[E.cy], E.cx);
  }

  if (E.cy < E.rowoff) {
    E.rowoff = E.cy;
  }
  if (E.cy >= E.rowoff + E.screenrows) {
    E.rowoff = E.cy - E.screenrows + 1;
  }

  if (E.rx < E.coloff) {
    E.coloff = E.rx;
  }
  if (E.rx >= E.coloff + E.screencolumns) {
    E.coloff = E.rx - E.screencolumns + 1;
  }
}

// like the base nvim well aslo draw `~` to the screen
void editorDrawRows(struct abuf *ab) {
  int y;

  for (y = 0; y < E.screenrows; y++) {

    int filerow = y + E.rowoff;

    if (filerow >= E.numrows) {
      if (E.numrows == 0 && y == E.screenrows / 3) {
        char welcome[80];
        int welcomelen = snprintf(welcome, sizeof(welcome),
                                  "Slate editor -- version %s", SLATE_VERSION);
        if (welcomelen > E.screencolumns)
          welcomelen = E.screencolumns;

        int padding = (E.screencolumns - welcomelen) / 2;
        if (padding) {
          abAppend(ab, "~", 1);
          padding--;
        }
        while (padding--)
          abAppend(ab, " ", 1);

        abAppend(ab, welcome, welcomelen);
      } else {
        abAppend(ab, "~", 1);
      }
    } else {
      int len = E.row[filerow].rsize - E.coloff;
      if (len < 0)
        len = 0;

      if (len > E.screencolumns)
        len = E.screencolumns;

      abAppend(ab, &E.row[filerow].render[E.coloff], len);
    }

    abAppend(ab, "\x1b[K", 3);
    abAppend(ab, "\r\n", 2);
  }
}

void editorDrawStatusBar(struct abuf *ab) {
  abAppend(ab, "\x1b[7m", 4);

  char status[80];
  char rstatus[80];

  int len = snprintf(status, sizeof(status), "%20s - %d lines",
                     E.filename ? E.filename : "[No Name :(]", E.numrows);

  int rlen = snprintf(rstatus, sizeof(rstatus), "%d/%d", E.cy + 1, E.numrows);

  if (len > E.screencolumns) {
    len = E.screencolumns;
  }

  abAppend(ab, status, len);

  while (len < E.screencolumns) {
    if (E.screencolumns - len == rlen) {
      abAppend(ab, rstatus, rlen);
      break;
    } else {
      abAppend(ab, " ", 1);
      len++;
    }
  }
  abAppend(ab, "\x1b[m", 3);
  abAppend(ab, "\r\n", 2);
}

void editorDrawMessageBar(struct abuf *ab) {
  abAppend(ab, "\x1b[K", 3);

  int msglen = strlen(E.statusmsg);

  if (msglen > E.screencolumns) {
    msglen = E.screencolumns;
  }

  if (msglen && time(NULL) - E.statusmsg_time < 5) {
    abAppend(ab, E.statusmsg, msglen);
  }
}

// as we have named it'll
// refresh the screen and
// lets clear the screen
void editorRefreshScreen() {

  editorScroll();

  struct abuf ab = ABUF_INIT;

  abAppend(&ab, "\x1b[?25l", 6);
  abAppend(&ab, "\x1b[H", 3);

  editorDrawRows(&ab);
  editorDrawStatusBar(&ab);
  editorDrawMessageBar(&ab);

  char buf[32];
  snprintf(buf, sizeof(buf), "\x1b[%d;%dH", (E.cy - E.rowoff) + 1,
           (E.rx - E.coloff) + 1);
  abAppend(&ab, buf, strlen(buf));

  abAppend(&ab, "\x1b[?25h", 6);

  // single write than
  // using multiple
  // that cause flickering
  write(STDOUT_FILENO, ab.b, ab.len);
  abFree(&ab);
}

// status bar msg
void editorSetStatusMessage(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vsnprintf(E.statusmsg, sizeof(E.statusmsg), fmt, ap);
  va_end(ap);
  E.statusmsg_time = time(NULL);
}
