#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#undef NDEBUG

#include "arbre.h"

#define LG 10

void copier_int(void *val, void **pt) {
  *pt = (int *)malloc(sizeof(int));
  memcpy(*pt, val, sizeof(int));
}

void afficher_int(void *val, FILE *f) { fprintf(f, "%d", *((int *)(val))); }

void detruire_int(void **pt) {
  if (*pt != NULL) {
    free(*pt);
    (*pt) = NULL;
  }
}

bool est_egal_int(void *val1, void *val2) {
  int a = *(int *)val1;
  int b = *(int *)val2;
  return (a == b);
}

void sommer(void *val, va_list vl) {
  int *pt_i = va_arg(vl, int *);
  (*pt_i) += *((int *)val);
}

void afficher_int_separes(void *val, va_list vl) {
  FILE *file = va_arg(vl, FILE *);
  bool *estPremier = va_arg(vl, bool *);
  if (*estPremier)
    *estPremier = false;
  else
    fprintf(file, " - ");
  afficher_int(val, file);
}

int main(void) {

  FILE *f_out = fopen("test_arbre_int_out.txt", "w");

  arbre a = arbre_creer(copier_int, detruire_int);

  srand(1234);

  int val = rand() % 30;
  fprintf(f_out, "racine = %d \n", val);
  arbre_inserer_racine(a, &val);

  arbre_parcours parcours = arbre_creer_parcours(a);

  for (int i = 0; i < LG; i++) {
    val = rand() % 30;
    fprintf(f_out, "insérer = %d \n", val);
    if (i % 2 == 0) {
      arbre_parcours_ajouter_fils_a_gauche(parcours, &val);
      arbre_parcours_aller_fils_gauche(parcours);
    } else if (i % 3 == 0)
      arbre_parcours_ajouter_frere_a_droite(parcours, &val);
    else {
      arbre_parcours_ajouter_frere_a_droite(parcours, &val);
      arbre_parcours_aller_frere_droit(parcours);
    }
  }

  arbre_parcours_detruire(parcours);

  arbre_afficher(a, f_out, afficher_int, " : ");
  arbre_afficher_tuple(a, f_out, afficher_int);

  val = 25;
  arbre a_extrait = arbre_extraction(a, &val, est_egal_int);

  fprintf(f_out, "arbre extrait : ");
  arbre_afficher(a_extrait, f_out, afficher_int, " : ");
  arbre_afficher_tuple(a_extrait, f_out, afficher_int);

  fprintf(f_out, "arbre restant : ");
  arbre_afficher(a, f_out, afficher_int, " : ");
  arbre_afficher_tuple(a, f_out, afficher_int);

  int s_ext = 0;
  arbre_parcourir(a_extrait, sommer, &s_ext);
  fprintf(f_out, "Somme arbre extrait : %d\n", s_ext);

  bool estPremier = true;
  arbre_parcourir(a_extrait, afficher_int_separes, f_out, &estPremier);
  fputc('\n', f_out);

  arbre_detruire(&a_extrait);

  int s_res = 0;
  arbre_parcourir(a, sommer, &s_res);
  fprintf(f_out, "Somme arbre restant : %d\n", s_res);

  estPremier = true;
  arbre_parcourir(a, afficher_int_separes, f_out, &estPremier);
  fputc('\n', f_out);

  arbre_detruire(&a);

  fclose(f_out);

  return 0;
}
