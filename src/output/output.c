#include "output.h"
#include "../terminal/terminal.h"
#include <unistd.h>

// like the base nvim well aslo draw `~` to the screen
void editorDrawRows() {
  int y;

  for (y = 0; y < E.screenrows; y++) {
    write(STDOUT_FILENO, "~", 1);

    if (y < E.screenrows - 1) {
      write(STDIN_FILENO, "\r\n", 2);
    }
  }
}

// as we have named it'll
// refresh the screen and
// lets clear the screen
void editorRefreshScreen() {
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);

  editorDrawRows();

  write(STDOUT_FILENO, "\x1b[H", 3);
}
