all:
	gcc -std=c11 -O2 -Iinclude \
    src/main.c src/render.c src/raster.c src/depthbuf.c \
    src/mesh.c src/mat.c src/vec.c src/sh_gfx.c \
    -lSDL2 -lm -o ./build/sr

clean:
	rm build/*
