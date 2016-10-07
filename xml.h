#ifndef __XML_H
#define __XML_H
#define SIZE 50

typedef struct balise_struct *balise;

balise balise_creer(char const *s);

void balise_detruire(balise *x);

bool est_egal_balise(void *val1, void *val2);

void afficher_balise(void *val, FILE *f);

arbre xml_construction_arbre(char *source);

#endif
