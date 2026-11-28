#ifndef KEYBOARD_H
#define KEYBOARD_H

enum editorKey {
  BACKSPACE = 127,
  ARROW_LEFT = 1000,
  ARROW_RIGHT,
  ARROW_UP,
  ARROW_DOWN,
  PAGE_UP,
  PAGE_DOWN,
  HOME_KEY,
  END_KEY,
  DEL_KEY,
};

void editorProcessKeypress(void);

int editorReadKey();

#endif // !KEYBOARD_H
#define KEYBOARD_H
