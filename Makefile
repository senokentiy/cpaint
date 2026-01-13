CC = gcc
CFLAGS = -g -Wall -Wextra
LIBS = -lm `sdl2-config --cflags --libs`
TARGET = cpaint
SOURCES = main.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LIBS)

clean:
	rm -f $(TARGET)

