CFLAGS=-std=c11 -O2
LDFLAGS=-lSDL2 -lm

TARGET=soft3d
SRC=src/main.c \
	src/render.c \
	src/raster.c \
	src/depthbuf.c \
    src/mesh.c \
	src/mat.c \
	src/vec.c \
	src/sh_gfx.c

all:
	gcc $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm $(TARGET)
