CFLAGS = -Wall -Wextra -pedantic -std=c99

slate: src/main.c src/terminal.h src/terminal.c
		$(CC) $(CFLAGS) src/main.c src/terminal.c -o slate
