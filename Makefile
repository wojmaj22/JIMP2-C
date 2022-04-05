main:
	gcc src/main.c src/generator.c src/bfs.c -o program -ggdb

clean:
	rm -f program