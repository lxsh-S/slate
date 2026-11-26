#include "../src/output/output.h"
#include "../src/read_input/keyboard.h"
#include "../src/terminal/terminal.h"

#define CTRL_KEY(k) ((k) & 0x1f)

int main() {

  // enable the raw mode
  enableRawMode();

  while (1) {
    editorProcessKeypress();

    // initialze editor
    initEditor();

    // clear the scrn
    editorRefreshScreen();
  }
}
