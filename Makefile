CC=gcc

main: src/main.o src/generator.o src/bfs.o src/djikstra.o src/czytacz.o
	$(CC) src/main.o src/generator.o src/bfs.o src/djikstra.o src/czytacz.o -o program.exe

debug: src/main.o src/generator.o src/bfs.o src/djikstra.o src/czytacz.o utilities/memwatch.o
	$(CC) src/main.o src/generator.o src/bfs.o src/djikstra.o src/czytacz.o utilities/memwatch.o -DMEMWATCH -DMEMWATCH_STDIO -o program.exe -ggdb 

clean:
	rm -f program.exe src/main.o src/generator.o src/bfs.o src/djikstra.o src/czytacz.o