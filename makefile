# C-2025 project base IK
all:
	gcc src/linkedlist.c -o bin/linkedlist.o -c -std=c99 -pedantic -Wall -g 
	gcc src/main.c -o bin/main.o -c -std=c99 -pedantic -Wall -g
	gcc main.o linkedlist.o -o bin/app

test:
	gcc -std=c99 -pedantic -Wall -Isrc test/test_hello.c src/hello.c -o bin/tests
	./bin/tests

memcheck:
	valgrind --leak-check=full ./bin/app

clean:
	rm -f bin/app bin/test
	rm -f bin/*.o