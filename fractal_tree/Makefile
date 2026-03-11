CFLAGS = -Wall -std=c23 $(shell pkg-config --cflags raylib)
LDFLAGS = $(shell pkg-config --libs raylib)

TARGET = fractal_tree
SRC = main.c

all: build run

build: 
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

run:
	./$(TARGET)
	rm ./$(TARGET)
