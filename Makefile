CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = fcc

SOURCES = src/main.c src/args.c src/lexer.c src/codegen.c src/compiler.c
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET) *.o *.s *.out test hello

test: $(TARGET)
	./fcc test/hello.c -o hello -v
	./hello

.PHONY: clean test
