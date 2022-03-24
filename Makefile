main:
	gcc src/main.c src/generator.c -o program

clean:
	rm -f program