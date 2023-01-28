.PHONY: build

CC := gcc
CFLAGS := -Wall -Wextra `sdl2-config --cflags` -lm
SDLFLAGS := `sdl2-config --libs`
BUILDDIR := build
TARGET := VoronoiDiagram
SRC := $(wildcard src/*.c)
OBJ := $(filter-out src/main.o, $(SRC:.c=.o))
INCLUDE := -I src -I include

all: $(OBJ)
	mkdir -p $(BUILDDIR)
	$(CC) -o $(BUILDDIR)/$(TARGET)  src/main.c $^ $(CFLAGS) $(SDLFLAGS)

%.o: %.c
	$(CC) -c $(INCLUDE) -o $@ $^ $(CFLAGS)

clean:
	$(RM) $(OBJ)

complete: clean all

run:
	./$(BUILDDIR)/$(TARGET)
