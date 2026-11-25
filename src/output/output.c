#include "output.h"

#include <unistd.h>

// lets clear the screen
void editorRefreshScreen() { write(STDOUT_FILENO, "\x1b[2J", 4); }
