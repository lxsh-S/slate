#include "output.h"

#include <unistd.h>

// like the base nvim well aslo draw `~` to the screen
void editorDrawRows() {
  int y;

  // currently dont know the size of the terminal
  // so using a hardcoded rows
  for (y = 0; y < 50; y++) {
    write(STDOUT_FILENO, "~\r\n", 3);
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
