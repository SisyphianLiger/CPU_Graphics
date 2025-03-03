build:
	gcc -Wall -std=c99 -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 ./src/*.c -o bin/renderer

run:
	bin/renderer

clean:
	rm bin/renderer
