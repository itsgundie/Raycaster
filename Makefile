
build:
	gcc -g -std=c99 ./src/*.c -I SDL/inc/ -L ./SDL/lib/ -lSDL2 -o raycaster

run:
	./raycaster

clean:
	rm raycaster