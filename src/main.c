#include "../src/file/file.h"
#include "../src/output/output.h"
#include "../src/read_input/keyboard.h"
#include "../src/terminal/terminal.h"

#define CTRL_KEY(k) ((k) & 0x1f)

int main(int argc, char *argv[]) {

  // enable the raw mode
  enableRawMode();

  // initialze editor once, not every frame
  initEditor();

  if (argc >= 2) {
    editorOpen(argv[1]);
  }

  editorSetStatusMessage("HELP: Ctrl-Q = quit");

  while (1) {
    editorProcessKeypress();

    // clear the scrn
    editorRefreshScreen();
  }
}
