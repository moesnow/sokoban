CC = gcc
CFLAGS = -Wall -Werror
TARGET = sokoban
SOURCE = sokoban.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)

