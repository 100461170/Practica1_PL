CC = gcc
C_FLAGS = -g -Wall -Werror
.PHONY: all clean

all: drLL
drLL: drLL.o
	$(CC) $(C_FLAGS) $< -o $@
drLL.o: drLL.c
	$(CC) $(C_FLAGS) $< -c -o $@

clean:
	rm -f drLL.o drLL