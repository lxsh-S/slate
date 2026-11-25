#include "../src/terminal/terminal.h"

#include "unistd.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>

#include "../src/read_input/keyboard.h"

#define CTRL_KEY(k) ((k) & 0x1f)

int main() {

  // enable the raw mode
  enableRawMode();

  while (1) {
    editorProcessKeypress();
  }
}
