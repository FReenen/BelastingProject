CC       := gcc
CURDIR   := $(shell pwd)

DEBUGDIR := $(CURDIR)/debug
SRCDIR := $(CURDIR)/src

main.o: src/main.c
	$(CC) -c $(SRCDIR)/main.c -o $(DEBUGDIR)/main.o

domeTimer: main.o
	$(CC) $(SRCDIR)/main.c -o $(CURDIR)/domeTimer

all: domeTimer

clean:
	rm -p domeTimer $(DEBUGDIR)/*