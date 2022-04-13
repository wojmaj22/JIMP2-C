

main: 
	gcc src/main.c src/generator.c src/bfs.c src/djikstra.c src/czytacz.c -o program.exe

debug: 
	gcc src/main.c src/generator.c src/bfs.c src/djikstra.c src/czytacz.c utilities/memwatch.c -DMEMWATCH -DMEMWATCH_STDIO -o program.exe -ggdb -DDEBUG

debug_mem: 
	gcc src/main.c src/generator.c src/bfs.c src/djikstra.c src/czytacz.c utilities/memwatch.c -DMEMWATCH -DMEMWATCH_STDIO -o program.exe -ggdb

clean:
	rm -f program.exe src/main.o src/generator.o src/bfs.o src/djikstra.o src/czytacz.o