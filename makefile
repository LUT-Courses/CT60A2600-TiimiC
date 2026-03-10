# Käytä make-komentoa kääntääksesi tiedostot
all:
	gcc src/main.c -o bin/main.o -c -std=c99 -pedantic -Wall -g
	gcc src/linkedlist.c -o bin/linkedlist.o -c -std=c99 -pedantic -Wall -g 
	gcc src/valikko/linkedlistValikko.c -o bin/linkedlistValikko.o -c -std=c99 -pedantic -Wall -g
	gcc src/valikko/binaaripuuValikko.c -o bin/binaaripuuValikko.o -c -std=c99 -pedantic -Wall -g
	gcc bin/main.o bin/linkedlist.o bin/linkedlistValikko.o bin/binaaripuuValikko.o -o bin/app

# Käännetään ja ajetaan testit
test:
	gcc -std=c99 -pedantic -Wall -Isrc test/test_hello.c src/hello.c -o bin/tests
	./bin/tests

# Muistivuotojen tarkistus valgrindillä
memcheck:
	valgrind --leak-check=full ./bin/app

# Puhdistetaan bin-kansio
clean:
	rm -f bin/app bin/test
	rm -f bin/*.o
