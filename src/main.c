#include "../src/output/output.h"
#include "../src/read_input/keyboard.h"
#include "../src/terminal/terminal.h"

#define CTRL_KEY(k) ((k) & 0x1f)

int main() {

  // enable the raw mode
  enableRawMode();

  // initialze editor once, not every frame
  initEditor();

  while (1) {
    editorProcessKeypress();

    // clear the scrn
    editorRefreshScreen();
  }
}
