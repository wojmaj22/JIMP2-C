main:
	gcc src/main.c src/generator.c src/bfs.c src/djikstra.c -o program

debug:
	gcc src/main.c src/generator.c src/bfs.c src/djikstra.c -o program -ggdb -Wall

clean:
	rm -f program