# Numéro du TDM
TDM_NUMERO := 4

## Compilation automatique de source C
# Compilteur
CC := gcc
#options de compilation
CFLAGS := -std=c99 -Wall -Wextra -pedantic -ggdb -Wno-unused-but-set-parameter -Wno-unused-variable -Wno-unused-parameter -Wno-unused-function -Wno-abi
# Règle de compilation

all : test_arbre_int test_arbre_xml

test_arbre_int : test_arbre_int.o arbre.o
	$(CC) $(CFLAGS) -o $@ $^

test_arbre_xml : test_arbre_xml.o chaine.o arbre.o xml.o
	$(CC) $(CFLAGS) -o $@ $^	

*.o : arbre.h
test_arbre_xml.o : arbre.h xml.h chaine.h
xml.o : arbre.h chaine.h
chaine.o : chaine.h

%.o: %.c 
	$(CC) $(CFLAGS) -o $@ -c $< 

test_int : test_arbre_int
	./test_arbre_int; diff -s -Z test_arbre_int_out.txt test_arbre_int_out_a_obtenir.txt


memoire_int : test_arbre_int
	valgrind --leak-check=full ./test_arbre_int


test_xml : test_arbre_xml
	./test_arbre_xml; diff -s -Z test_arbre_xml_out.txt test_arbre_xml_out_a_obtenir.txt


memoire_xml : test_arbre_xml
	valgrind --leak-check=full ./test_arbre_xml



clean:
	rm *.o

#
# Pour faire l'archive de remise
#
TGZ_FILES :=  *.c *.h ?akefile cr.pdf
TDM_DIR := TDM$(TDM_NUMERO)

rendu :
	[ -e cr.pdf ] || echo > cr.pdf
	cd .. ; tar czf $(TDM_DIR)/rendu.tgz $(TGZ_FILES:%=$(TDM_DIR)/%)

indent :
	indent --blank-lines-after-declarations --blank-lines-after-procedures -br -bc  --blank-lines-after-commas -bl --braces-on-if-line --braces-on-func-def-line  --space-after-cast  --leave-preprocessor-space  --space-after-procedure-calls --space-after-parentheses --space-after-for --space-after-for --space-after-while --space-special-semicolon -bfda < arbre.h 
#	indent -orig  < arbre.h

