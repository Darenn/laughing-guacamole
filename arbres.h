#ifndef ARBRES
#define ARBRES

#include <stdbool.h>
#include <stdio.h>

typedef struct noeud_struct *noeud;

noeud noeud_creer_vide();
noeud noeud_creer(void *val, void (*copier)(void *val, void **ptr));
void noeud_detruire(noeud *n, void (*detruire)(void **val));

void noeud_ajouter_filsgauche(noeud n, void *val,
                              void (*copier)(void *val, void **ptr));
void noeud_ajouter_freredroit(noeud n, void *val,
                              void (*copier)(void *val, void **ptr));

void noeud_afficher(noeud n, void (*afficher)(void *val, FILE *f), FILE *f);

noeud *noeud_rechercher(noeud *n, void *val,
                        bool (*est_egal)(void *val1, void *val2));

typedef struct arbre_struct *arbre;

arbre arbre_creer(void (*_copier)(void *val, void **pt),
                  void (*_afficher)(void *val, FILE *f),
                  void (*_detruire)(void **pt));
void arbre_detruire(arbre *a);
void arbre_afficher(arbre a, FILE *f);

void arbre_init_courant(arbre a);
void arbre_courant_filsgauche(arbre a);
void arbre_courant_freredroit(arbre a);
void arbre_courant_pere(arbre a);
bool arbre_courant_sans_filsgauche(arbre a);

void arbre_inserer_racine(arbre a, void *val);

void arbre_ajouter_filsgauche_courant(arbre a, void *val);
void arbre_ajouter_freredroit_courant(arbre a, void *val);
void arbre_ajouter_fils_courant(arbre a, void *val);

arbre arbre_extraction(arbre a, void *val,
                       bool (*est_egal)(void *val1, void *val2));

#endif
