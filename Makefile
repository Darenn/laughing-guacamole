## Compilation automatique de source C
# Compilteur
CC := gcc
#options de compilation
CFLAGS := -std=c99 -Wall -Wextra -pedantic -ggdb -Wno-unused-but-set-parameter -Wno-unused-variable -Wno-unused-parameter -Wno-abi
# Règle de compilation

all : test_arbres_int test_arbres_xml

test_arbres_int : test_arbres_int.o arbres.o
	$(CC) $(CFLAGS) -o $@ $^

test_arbres_xml : test_arbres_xml.o chaine.o arbres.o xml.o
	$(CC) $(CFLAGS) -o $@ $^	

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< 

test_int : test_arbres_int
	./test_arbres_int


memoire_int : test_arbres_int
	valgrind --leak-check=full ./test_arbres_int


test_xml : test_arbres_xml
	./test_arbres_xml


memoire_xml : test_arbres_xml
	valgrind --leak-check=full ./test_arbres_xml



clean:
	rm *.o
