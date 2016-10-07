#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#undef NDEBUG

#include "arbre.h"
#include "chaine.h"
#include "xml.h"

struct balise_struct {
  enum { ouvrante, fermante } type;
  chaine nom;
};

// A partir d'une chaîne de caractères correspondant à une balise ( <xxx> ou
// </xxx> )
// on construit un balise avec ses deux champs nom et type.
balise balise_creer(char const *st) {
  // Creation de la balise
  balise b = (balise)malloc(sizeof(struct balise_struct));
  assert(b != NULL);
  // Creation du nom de la balise
  char *nom = (char *)malloc(sizeof(char) * strlen(st));
  assert(nom != NULL);
  // Copie du string passé en parametre
  strncpy(nom, st, strlen(st) - 1);
  // Si c'est une balise fermante
  if (*(nom + 1) == '/') {
    b->type = fermante;
    b->nom = chaine_creer_char(nom + 2);
  } else {
    b->type = ouvrante;
    b->nom = chaine_creer_char(nom + 1);
  }
  free(nom);
  return b;
}

// renvoie vrai si c'est une balise ouvrante
bool balise_est_ouvrante(balise x) {
  assert(x != NULL);
  return (x->type == ouvrante);
}

// renvoie vrai si c'est une balise fermante
bool balise_est_fermante(balise x) {
  assert(x != NULL);
  return (x->type == fermante);
}

// destruction d'un balise
void balise_detruire(balise *x) {
  if (*x != NULL) {
    chaine_detruire(&(*x)->nom);
    free(*x);
    *x = NULL;
  }
}

// affichage ( simplement le nom )
static void balise_afficher(balise x, FILE *f) { chaine_afficher(f, x->nom); }

// Les 4 fonctions ci-dessous sont usuels maintenant pour la manipulation d'un
// arbre de balises...
static void copier_balise(void *val, void **ptr) {
  balise in = (balise)val;
  balise *out = (balise *)ptr;
  *out = malloc(sizeof(struct balise_struct));
  ((balise)*out)->type = in->type;
  ((balise)*out)->nom = chaine_copier(in->nom);
}

void afficher_balise(void *val, FILE *f) { balise_afficher((balise)val, f); }

void detruire_balise(void **ptr) { balise_detruire((balise *)ptr); }

bool est_egal_balise(void *val1, void *val2) {
  balise b1 = (balise)val1;
  balise b2 = (balise)val2;
  return b1->type == b2->type && chaine_est_egal(b1->nom, b2->nom);
}

// Retourne un pointeur sur le premier char qui n'est pas un espace et
// et met un 0 de manière à supprimer les derniers espaces.
static char *trim(char *st) {
  assert(st != NULL);
  // Work position
  char *current = st;
  // Go to the first non space character
  while (isspace(*current)) {
    current++;
  };
  st += strlen(st);
  // Back to the last non space character
  while (isspace(*--st)) {
  };
  // End of string after the last non space character
  st = 0;
  return current;
}

/* Pour construire un arbre en lisant un fichier XML simple ne contenant qu'une
 * serie de balises */
/* on supposera ce fichier bien formé au sens XML. */
arbre xml_construction_arbre(char *source) {
  // Le fichier
  FILE *fp = fopen(source, "r");
  assert(fp != NULL);
  // La ligne courante
  char line[1024];
  // L'arbre
  arbre a = arbre_creer(&copier_balise, &detruire_balise);
  assert(a != NULL);
  // Ajout de la racine
  fscanf(fp, "%1023s", line);
  arbre_inserer_racine(a, balise_creer(line));
  // Le parcour
  arbre_parcours ap = arbre_creer_parcours(a);
  assert(ap != NULL);

  // Pour chaque ligne
  while (fscanf(fp, "%1023s", line) != EOF) {
    balise b = balise_creer(line);
    if (balise_est_fermante(b)) {
      if (arbre_parcours_a_pere(ap)) {
        arbre_parcours_aller_pere(ap);
      }
    } else {
      arbre_parcours_ajouter_fils_a_droite(ap, b);
      arbre_parcours_aller_fils_droite(ap);
    }
  }

  // Fermeture du fichier
  fclose(fp);
  // On retourne l'arbre
  return a;
}
