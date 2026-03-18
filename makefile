# Käytä make-komentoa kääntääksesi tiedostot
all:
	gcc src/main.c -o bin/main.o -c -std=c99 -pedantic -Wall -g
	gcc src/linkedlist.c -o bin/linkedlist.o -c -std=c99 -pedantic -Wall -g
	gcc src/binarytree.c -o bin/binarytree.o -c -std=c99 -pedantic -Wall -g
	gcc src/valikko/linkedlistValikko.c -o bin/linkedlistValikko.o -c -std=c99 -pedantic -Wall -g
	gcc src/valikko/binaaripuuValikko.c -o bin/binaaripuuValikko.o -c -std=c99 -pedantic -Wall -g
	gcc bin/main.o bin/linkedlist.o bin/binarytree.o bin/linkedlistValikko.o bin/binaaripuuValikko.o -o bin/app

# Käännetään ja ajetaan testit
test:
	gcc -std=c99 -pedantic -Wall -Isrc test/test_hello.c src/hello.c -o bin/tests
	./bin/tests

test_binarytree:
	gcc -std=c99 -pedantic -Wall \
	-Isrc -Iunity/Unity/src \
	test/test_binarytree.c src/binarytree.c unity/Unity/src/unity.c \
	-o bin/test_binarytree
	./bin/test_binarytree

# Muistivuotojen tarkistus valgrindillä
memcheck:
	valgrind --leak-check=full ./bin/app

# Puhdistetaan bin-kansio
clean:
	rm -f bin/app bin/test bin/test_binarytree
	rm -f bin/*.o

# Luo dokumentaatio Doxygenilla
docs:
	doxygen doc/Doxyfile