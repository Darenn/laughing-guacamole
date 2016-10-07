#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef NDEBUG

#include "arbre.h"

/*
 * Peu d'assert sur les fonctions static car elles ne peuvent être appelées que
 * du module qui garantit la validité des données.
 * Certains existent néanmoins pour la mise au point du module.
 */

/*!
 * Représente un noeud de l'arbre (Pointeur/référence).
 */
typedef struct noeud_struct *noeud;

/*!
* \struct noeud_struct arbres.h noeud
* \brief Représente un noeud d'un arbre.
* Contient un pointeur vers son père, son fils gauche (son noeud fils le plus à
* gauche) et vers son frere droit (un noeud frère a le même père, le frère droit
* est directement à droite du noeud).
*/
struct noeud_struct {
  void *val;
  noeud pere;
  noeud fils_gauche;
  noeud frere_droit;
};

/*!
* \brief Créer un noeud vide (attributs à NULL) et le retourne.
* \return Un noeud vide.
*/
noeud noeud_creer_vide() {
  noeud n = (noeud)malloc(sizeof(struct noeud_struct));
  n->val = NULL;
  n->pere = NULL;
  n->fils_gauche = NULL;
  n->frere_droit = NULL;
  return n;
}

/*!
* \brief Créer un noeud avec pour valeur val.
* \param val La valeur du noeud.
* \param Un pointeur vers une fonction permettant de copier un valeur.
* \return Un noeud avec pour valeur val.
* \pre Les paramètres doivent être définis.
*/
noeud noeud_creer(void *val, void (*copier)(void *val, void **ptr)) {
  assert(val != NULL);
  assert(copier != NULL);
  noeud n = (noeud)malloc(sizeof(struct noeud_struct));
  copier(val, &(n->val));
  n->pere = NULL;
  n->fils_gauche = NULL;
  n->frere_droit = NULL;
  return n;
}

/*!
* \brief Créer un noeud avec pour valeur val, qui devient le fils gauche de n.
* \param n Le noeud auquel on veut ajouter le fils à gauche.
* \param val La valeur que prendra le fils gauche.
* \param copier Un pointeur vers une fonction qui permet de copier une valeur.
* \pre Les paramètres doivent être définis.
*/
void noeud_ajouter_fils_a_gauche(noeud n, void *val,
                                 void (*copier)(void *val, void **ptr)) {
  assert(NULL != n);
  assert(copier != NULL);
  noeud fg = noeud_creer(val, copier);
  fg->pere = n;
  fg->frere_droit = n->fils_gauche;
  n->fils_gauche = fg;
}

/*!
* \brief Créer un noeud avec pour valeur val, qui devient le frere droit du
* frere le plus à droite de n.
* \param n Le noeud auquel on veut ajouter le frere le plus à droite.
* \param val La valeur que prendra le frere droit.
* \param copier Un pointeur vers une fonction qui permet de copier une valeur.
* \pre Les paramètres doivent être définis.
*/
void noeud_ajouter_frere_a_droite(noeud n, void *val,
                                  void (*copier)(void *val, void **ptr)) {
  assert(NULL != n);
  assert(copier != NULL);
  noeud fd = noeud_creer(val, copier);
  fd->pere = n->pere;
  while (n->frere_droit != NULL)
    n = n->frere_droit;
  n->frere_droit = fd;
}

/*!
* \brief Créer un noeud avec pour valeur val, qui devient le fils le plus à
* droite de n.
* \param n Le noeud auquel on veut ajouter le frere à droite.
* \param val La valeur que prendra le frere droit.
* \param copier Un pointeur vers une fonction qui permet de copier une valeur.
* \pre Les paramètres doivent être définis.
*/
void noeud_ajouter_fils(noeud n, void *val,
                        void (*copier)(void *val, void **ptr)) {
  assert(NULL != n);
  assert(copier != NULL);
  if (n->fils_gauche == NULL)
    noeud_ajouter_fils_a_gauche(n, val, copier);
  else
    noeud_ajouter_frere_a_droite(n->fils_gauche, val, copier);
}

/*!
* \brief Affiche le sous-arbre ayant pour racine le noeud n sur le flux f avec
* la fonction afficher.
* \param n Le noeud qui sera la racine du sous-arbre que l'on souhaite afficher.
* \param afficher Un pointeur vers une fonction qui affiche une valeur sur un
* flux.
* \param f Le flux sur lequel afficher le sous-arbre.
* \pre Les paramètres afficher et f doivent être définis.
*/
void noeud_afficher(noeud n, void (*afficher)(void *val, FILE *f), FILE *f,
                    char const *const sep) {
  assert(afficher != NULL);
  assert(f != NULL);
  if (n != NULL) {
    if (n->pere != NULL)
      fprintf(f, "%s", sep);
    afficher(n->val, f);
    noeud_afficher(n->fils_gauche, afficher, f, sep);
    noeud_afficher(n->frere_droit, afficher, f, sep);
  }
}

/*!
* \brief Affiche le sous-arbre ayant pour racine le noeud n sur le flux f avec
* la fonction afficher.
* \param n Le noeud qui sera la racine du sous-arbre que l'on souhaite afficher.
* \param afficher Un pointeur vers une fonction qui affiche une valeur sur un
* flux.
* \param f Le flux sur lequel afficher le sous-arbre.
* \pre Les paramètres afficher et f doivent être définis.
*/
void noeud_afficher_tuple(noeud n, void (*afficher)(void *val, FILE *f),
                          FILE *f) {
  assert(afficher != NULL);
  assert(f != NULL);
  if (n != NULL) {
    afficher(n->val, f);
    if (n->fils_gauche != NULL) {
      fprintf(f, " ( ");
      noeud_afficher_tuple(n->fils_gauche, afficher, f);
      fprintf(f, " )");
    }
    if (n->frere_droit) {
      fprintf(f, " , ");
      noeud_afficher_tuple(n->frere_droit, afficher, f);
    }
  }
}

/*!
* \brief Détruit tout les noeuds du sous-arbre ayant pour racine le noeud n.
* \param n Le noeud racine du sous-arbre que l'on veut détruire.
* \param detruire Un pointeur vers une fonction qui détruit une valeur.
* \pre detruire être défini.
*/
void noeud_detruire(noeud *n, void(detruire)(void **val)) {
  assert(detruire != NULL);
  if ((*n) != NULL) {
    noeud_detruire(&((*n)->fils_gauche), detruire);
    noeud_detruire(&((*n)->frere_droit), detruire);
    detruire(&((*n)->val));
    free(*n);
    *n = NULL;
  }
}

/*!
* \brief Recherche un noeud avec pour valeur val dans le sous-arbre ayant pour
* racine le noeud pointé par n en suivant un parcours prefixe.
* \param n Un pointeur vers le noeud racine du sous-arbre dans le lequel on
* recherche la valeur.
* \param val La valeur recherchée.
* \param est_egal Un pointeur vers une fonction qui indique si deux valeurs sont
* égales.
* \pre val et est_egal doivent être définis.
* \return Un pointeur vers le noeud racine ayant pour valeur val du sous-arbre.
*/
noeud *noeud_rechercher(noeud *n, void *val,
                        bool (*est_egal)(void *val1, void *val2)) {
  assert(val != NULL);
  assert(est_egal != NULL);
  if (*n == NULL)
    return (noeud *)NULL;
  else {
    if (est_egal((*n)->val, val))
      return n;
    else {
      noeud *valg = noeud_rechercher(&(*n)->fils_gauche, val, est_egal);
      if (valg != NULL)
        return valg;
      else
        return noeud_rechercher(&(*n)->frere_droit, val, est_egal);
    }
  }
}

struct arbre_struct {
  noeud
      racine; // pointe sur la racine de l'arbre (le noeud qui n'a pas de père)
  void (*copier)(void *val,
                 void **pt);   // pour copier/mettre ne place une valeur
  void (*detruire)(void **pt); // pour détruire une valeur stockée dans l'arbre
};

arbre arbre_creer(void (*copier)(void *val, void **pt),
                  void (*detruire)(void **pt)) {
  assert(NULL != copier);
  assert(NULL != detruire);
  arbre n = (arbre)malloc(sizeof(struct arbre_struct));
  assert(NULL != n);
  n->racine = NULL;
  n->copier = copier;
  n->detruire = detruire;
  return n;
}

void arbre_detruire(arbre *a) {
  assert(NULL != a);
  noeud_detruire(&((*a)->racine), (*a)->detruire);
  free(*a);
  *a = NULL;
}

void arbre_inserer_racine(arbre a, void *val) {
  assert(NULL != a);
  assert(NULL != val);
  noeud n = noeud_creer(val, a->copier);
  n->fils_gauche = a->racine;
  a->racine = n;
}

// affichage de l'arbre avec un passage à la ligne en fin
void arbre_afficher(arbre a, FILE *f, void (*afficher)(void *val, FILE *f),
                    char const *const sep) {
  assert(NULL != a);
  assert(NULL != f);
  assert(NULL != afficher);
  noeud_afficher(a->racine, afficher, f, sep);
  fputc('\n', f);
}

// affichage de l'arbre avec parenthèses et virgules et un passage à la ligne en
// fin
void arbre_afficher_tuple(arbre a, FILE *f,
                          void (*afficher)(void *val, FILE *f)) {
  assert(NULL != a);
  assert(NULL != f);
  assert(NULL != afficher);
  noeud_afficher_tuple(a->racine, afficher, f);
  fputc('\n', f);
}

// on extrait l'arbre à partir du noeud n qui contient la valeur recherchée
// la fonction renvoie l'arbre dont la racine est n
// et l'arbre initial ne contient plus ce arbre extrait
// si la valeur n'existe pas on renvoie NULL
// courant doit etre initialisé à la racine dans les 2 cas.
arbre arbre_extraction(arbre a, void *val,
                       bool (*est_egal)(void *val1, void *val2)) {
  assert(a != NULL);
  assert(val != NULL);
  assert(est_egal != NULL);
  noeud *noeudRecherche = noeud_rechercher(&(a)->racine, val, est_egal);
  arbre arbreExtrait = NULL;
  if (noeudRecherche != NULL) {
    arbreExtrait = arbre_creer(a->copier, a->detruire);
    arbreExtrait->racine = *noeudRecherche;
    arbreExtrait->racine->pere = NULL;
    *noeudRecherche = arbreExtrait->racine->frere_droit;
    arbreExtrait->racine->frere_droit = NULL;
  }
  return arbreExtrait;
}

// Enregistre l'arbre à parcourir et le nœud où en est le parcours.
struct arbre_parcours_struct {
  arbre a;
  noeud courant; // vaut NULL quand le parcours est fini
};

arbre_parcours arbre_creer_parcours(arbre a) {
  assert(a != NULL);
  arbre_parcours ap =
      (arbre_parcours)malloc(sizeof(struct arbre_parcours_struct));
  ap->a = a;
  if (a->racine != NULL)
    ap->courant = a->racine;
  else
    ap->courant = NULL;
  return ap;
}

void arbre_parcours_detruire(arbre_parcours p) {
  assert(p != NULL);
  free(p);
}

bool arbre_parcours_est_fini(arbre_parcours p) {
  assert(p != NULL);
  return p->courant == NULL;
}

// 1er fils
// puis frère à droite
// puis frère à droite du premier en ancestre ayant un
void arbre_parcours_suivant(arbre_parcours p) {
  assert(p != NULL);
  if (p->courant->fils_gauche != NULL) {
    p->courant = p->courant->fils_gauche;
  } else {
    while (p->courant->frere_droit == NULL && p->courant->pere != NULL) {
      p->courant = p->courant->pere;
    }
    p->courant = p->courant->frere_droit;
  }
}

void *arbre_parcours_valeur(arbre_parcours p) {
  assert(p != NULL);
  return p->courant->val;
}

bool arbre_parcours_a_fils(arbre_parcours p) {
  assert(!arbre_parcours_est_fini(p));
  return (NULL != p->courant->fils_gauche);
}

void arbre_parcours_aller_fils_gauche(arbre_parcours p) {
  assert(arbre_parcours_a_fils(p));
  p->courant = p->courant->fils_gauche;
}

void arbre_parcours_aller_fils_droite(arbre_parcours p) {
  assert(p != NULL);
  p->courant = p->courant->fils_gauche;
  while (p->courant->frere_droit != NULL) {
    p->courant = p->courant->frere_droit;
  }
}

bool arbre_parcours_a_frere_droit(arbre_parcours p) {
  return p->courant->frere_droit != NULL;
}

void arbre_parcours_aller_frere_droit(arbre_parcours p) {
  p->courant = p->courant->frere_droit;
}

bool arbre_parcours_a_pere(arbre_parcours p) {
  assert(!arbre_parcours_est_fini(p));
  return (NULL != p->courant->pere);
}

void arbre_parcours_aller_pere(arbre_parcours p) {
  assert(arbre_parcours_a_pere(p));
  p->courant = p->courant->pere;
}

void arbre_parcours_ajouter_frere_a_droite(arbre_parcours p, void *val) {
  assert(!arbre_parcours_est_fini(p));
  noeud_ajouter_frere_a_droite(p->courant, val, p->a->copier);
}

void arbre_parcours_ajouter_fils_a_gauche(arbre_parcours p, void *val) {
  assert(!arbre_parcours_est_fini(p));
  noeud_ajouter_fils_a_gauche(p->courant, val, p->a->copier);
}

void arbre_parcours_ajouter_fils_a_droite(arbre_parcours p, void *val) {
  assert(!arbre_parcours_est_fini(p));
  noeud_ajouter_fils(p->courant, val, p->a->copier);
}

void arbre_parcourir(arbre a, void (*faire)(void *val1, va_list args), ...) {
  assert(NULL != a);
  assert(NULL != faire);
  arbre_parcours p = arbre_creer_parcours(a);
  while (!arbre_parcours_est_fini(p)) {
    va_list va;
    va_start(va, faire);
    (*faire)(arbre_parcours_valeur(p), va);
    va_end(va);
    arbre_parcours_suivant(p);
  }
  arbre_parcours_detruire(p);
}
