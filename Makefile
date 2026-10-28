CC = gcc
CFLAGS = -Wall -O2 -Wextra

twee: main.c
	$(CC) $(CFLAGS) $< -o $@ 

debug: CFLAGS += -g
debug: twee

clean:
	rm -f twee
