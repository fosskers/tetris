TARGET=fetris
WARNINGS=-Wall -Wshadow -Wunreachable-code
CFLAGS=$(WARNINGS) -g -O
LDFLAGS=-lGL -lglfw -lGLEW -lpthread -lm
HEADERS=cog/shaders/shader.h cog/dbg.h cog/colour.h cog/linalg/linalg.h cog/camera/camera.h block.h util.h collision.h
OBJECTS=cog/shaders/shaders.o cog/linalg/linalg.o cog/camera/camera.o block.o util.o collision.o fetris.o
COMPILER=clang

default: $(TARGET)
all: default

%.o: %.c $(HEADERS)
	$(COMPILER) $(CFLAGS) -c $< -o $@

fetris: $(OBJECTS)
	$(COMPILER) $(OBJECTS) $(CFLAGS) $(LDFLAGS) -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)

# Compile Check
cc:
	make clean
	make all
