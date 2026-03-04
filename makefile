# C-2025 project base IK
all:
	gcc -std=c99 -pedantic -Wall -g src/main.c -o bin/app

test:
	gcc -std=c99 -pedantic -Wall -Isrc test/test_hello.c src/hello.c -o bin/tests
	./bin/tests

memcheck:
	valgrind --leak-check=full ./bin/app

clean:
	rm -f bin/app bin/test