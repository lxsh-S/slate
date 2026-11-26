CC = cc

CFLAGS = -Wall -Wextra -pedantic -std=c99 -Isrc

SRCS = src/main.c \
			 src/output/output.c \
			 src/read_input/keyboard.c \
			 src/terminal/terminal.c

OBJS = $(SRCS:.c=.o)

slate: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o slate

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) slate

.PHONY: clean
