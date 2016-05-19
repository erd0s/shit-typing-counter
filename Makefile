CC=gcc
CFLAGS=-framework ApplicationServices -framework Carbon -lncurses
SOURCES=counter.c
EXECUTABLE=counter

all: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE)