main:
	gcc src/main.c src/generator.c src/bfs.c src/djikstra.c src/czytacz.c -o program.exe

debug:
	gcc src/main.c src/generator.c src/bfs.c src/djikstra.c src/czytacz.c utilities/memwatch.c -DMEMWATCH -DMEMWATCH_STDIO -o program.exe -ggdb 

clean:
	rm -f program