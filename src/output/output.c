#include "output.h"
#include "../terminal/terminal.h"
#include <unistd.h>

// like the base nvim well aslo draw `~` to the screen
void editorDrawRows(struct abuf *ab) {
  int y;

  for (y = 0; y < E.screenrows; y++) {
    abAppend(ab, "~", 1);

    if (y < E.screenrows - 1) {
      abAppend(ab, "\r\n", 2);
    }
  }
}

// as we have named it'll
// refresh the screen and
// lets clear the screen
void editorRefreshScreen() {
  struct abuf ab = ABUF_INIT;

  abAppend(&ab, "\x1b[2J", 4);
  abAppend(&ab, "\x1b[H", 3);

  editorDrawRows(&ab);
  abAppend(&ab, "\x1b[H", 3);
  abAppend(&ab, "\x1b[?25h", 6);

  // single write than
  // using multiple
  // that cause flickering
  write(STDOUT_FILENO, ab.b, ab.len);
  abFree(&ab);
}
