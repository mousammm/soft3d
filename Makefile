all:
	gcc -o ./build/sr ./src/main.c -lSDL2 -lm

run:
	@./build/sr

clean:
	rm build/*
