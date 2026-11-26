#ifndef KEYBOARD_H
#define KEYBOARD_H

enum editorKey {
  ARROW_LEFT = 'a',
  ARROW_RIGHT = 'd',
  ARROW_UP = 'w',
  ARROW_DOWN = 's'
};

void editorProcessKeypress(void);

void editorReadKey();

#endif // !KEYBOARD_H
#define KEYBOARD_H
