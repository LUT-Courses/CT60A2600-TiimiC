# C-2025 project base IK
all:
	gcc src/linkedlist.c -c -std=c99 -pedantic -Wall -g 
	gcc src/main.c -c -std=c99 -pedantic -Wall -g
	gcc src/main.o src/linkedlist.o -o bin/app

test:
	gcc -std=c99 -pedantic -Wall -Isrc test/test_hello.c src/hello.c -o bin/tests
	./bin/tests

memcheck:
	valgrind --leak-check=full ./bin/app

clean:
	rm -f bin/app bin/test