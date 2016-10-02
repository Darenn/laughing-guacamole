#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arbres.h"

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
  noeud filsgauche;
  noeud freredroit;
};

/*!
* \brief Créer un noeud vide (attributs à NULL) et le retourne.
* \return Un noeud vide.
*/
noeud noeud_creer_vide() {
  noeud n = (noeud)malloc(sizeof(struct noeud_struct));
  n->val = NULL;
  n->pere = NULL;
  n->filsgauche = NULL;
  n->freredroit = NULL;
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
  n->filsgauche = NULL;
  n->freredroit = NULL;
  return n;
}

/*!
* \brief Créer un noeud avec pour valeur val, qui devient le fils gauche de n.
* \param n Le noeud auquel on veut ajouter le fils à gauche.
* \param val La valeur que prendra le fils gauche.
* \param copier Un pointeur vers une fonction qui permet de copier une valeur.
* \pre Les paramètres doivent être définis.
*/
void noeud_ajouter_filsgauche(noeud n, void *val,
                              void (*copier)(void *val, void **ptr)) {
  assert(NULL != n);
  assert(copier != NULL);
  noeud fg = noeud_creer(val, copier);
  fg->pere = n;
  fg->freredroit = n->filsgauche;
  n->filsgauche = fg;
}

/*!
* \brief Créer un noeud avec pour valeur val, qui devient le frere droit du
* frere le plus à droite de n.
* \param n Le noeud auquel on veut ajouter le frere le plus à droite.
* \param val La valeur que prendra le frere droit.
* \param copier Un pointeur vers une fonction qui permet de copier une valeur.
* \pre Les paramètres doivent être définis.
*/
void noeud_ajouter_freredroit(noeud n, void *val,
                              void (*copier)(void *val, void **ptr)) {
  assert(NULL != n);
  assert(copier != NULL);
  noeud fd = noeud_creer(val, copier);
  fd->pere = n->pere;
  while (n->freredroit != NULL)
    n = n->freredroit;
  n->freredroit = fd;
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
  if (n->filsgauche == NULL)
    noeud_ajouter_filsgauche(n, val, copier);
  else
    noeud_ajouter_freredroit(n->filsgauche, val, copier);
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
void noeud_afficher(noeud n, void (*afficher)(void *val, FILE *f), FILE *f) {
  assert(afficher != NULL);
  assert(f != NULL);
  if (n != NULL) {
    afficher(n->val, f);
    noeud_afficher(n->filsgauche, afficher, f);
    noeud_afficher(n->freredroit, afficher, f);
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
    noeud_detruire(&((*n)->filsgauche), detruire);
    noeud_detruire(&((*n)->freredroit), detruire);
    detruire(&((*n)->val));
    free(*n);
    *n = NULL;
  }
}

/*!
* \brief Recherche un noeud avec pour valeur val dans le sous-arbre de racine n
* en suivant un parcours prefixe.
* \param n Le noeud racine du sous-arbre dans le lequel on recherche la valeur.
* \param val La valeur recherchée.
* \param est_egal Un pointeur vers une fonction qui indique si deux valeurs sont
* égales.
* \pre val et est_egal doivent être définis.
* \return Un sous-arbre ayant pour racine un noeud avec pour valeur val.
*/
noeud noeud_rechercher(noeud n, void *val,
                       bool (*est_egal)(void *val1, void *val2)) {
  assert(val != NULL);
  assert(est_egal != NULL);
  if (n == NULL)
    return NULL;
  else {
    if (est_egal(n->val, val))
      return n;
    else {
      noeud valg = noeud_rechercher(n->filsgauche, val, est_egal);
      if (valg != NULL)
        return valg;
      else
        return noeud_rechercher(n->freredroit, val, est_egal);
    }
  }
}

struct arbre_struct {
  noeud
      racine; // pointe sur la racine de l'arbre (le noeud qui n'a pas de père)
  noeud courant; // permet de se déplacer dans l'arbre
  void (*copier)(void *val, void **pt);
  void (*afficher)(void *val, FILE *f);
  void (*detruire)(void **pt);
};

// la tete et courant sont à NULL
arbre arbre_creer(void (*_copier)(void *val, void **pt),
                  void (*_afficher)(void *val, FILE *f),
                  void (*_detruire)(void **pt)) {
  assert(_copier != NULL);
  assert(_afficher != NULL);
  assert(_detruire != NULL);
  arbre a = (arbre)malloc(sizeof(struct arbre_struct));
  a->racine = NULL;
  a->courant = NULL;
  a->copier = _copier;
  a->afficher = _afficher;
  a->detruire = _detruire;
  return a;
}

// Destruction compléte de l'arbre
void arbre_detruire(arbre *a) {
  assert(a != NULL);
  noeud_detruire(&(*a)->racine, (*a)->detruire);
}

// Initialisation de courant à la tete de l'arbre
void arbre_init_courant(arbre a) {
  assert(a != NULL);
  a->courant = a->racine;
}

// On déplace courant sur son fils gauche
void arbre_courant_filsgauche(arbre a) {
  assert(a != NULL);
  a->courant = a->courant->filsgauche;
}

// On déplace courant sur son père
void arbre_courant_pere(arbre a) {
  assert(a != NULL);
  a->courant = a->courant->pere;
}

// renvoie vrai si courant n'a pas de fils gauche
bool arbre_courant_sans_filsgauche(arbre a) {
  assert(a != NULL);
  return a->courant->filsgauche == NULL;
}

// On déplace courant sur son frere droit
void arbre_courant_freredroit(arbre a) {
  assert(a != NULL);
  a->courant = a->courant->freredroit;
}

// affichage de l'arbre avec un passage à la ligne en fin
void arbre_afficher(arbre a, FILE *f) {
  assert(a != NULL);
  assert(f != NULL);
  noeud_afficher(a->racine, a->afficher, f);
  fprintf(f, "\n");
}

// On insère une racine (nouvelle ou pas) à l'arbre
void arbre_inserer_racine(arbre a, void *val) {
  assert(a != NULL);
  assert(val != NULL);
  noeud racine = noeud_creer(val, a->copier);
  // Si l'arbre a une racine, celle-ci devient le fils gauche de la nouvelle
  // racine, qui elle même devient le père de l'ancienne racine
  if (a->racine != NULL) {
    racine->filsgauche = a->racine;
    a->racine->pere = racine;
  }
  a->racine = racine;
}

// On ajoute un fils gauche à partir de courant
// Si courant a déjà un fils gauche il devient un frère droit du nouveau fils
// gauche
void arbre_ajouter_filsgauche_courant(arbre a, void *val) {
  assert(a != NULL);
  assert(val != NULL);
  noeud_ajouter_filsgauche(a->courant, val, a->copier);
}

// On ajoute un frere droit à partir de courant
// rajouté à la fin des frères droits déjà existants
void arbre_ajouter_freredroit_courant(arbre a, void *val) {
  assert(a != NULL);
  assert(val != NULL);
  noeud_ajouter_freredroit(a->courant, val, a->copier);
}

// On ajoute un fils soit comme fils gauche s'il n'existe pas
// soit comme un frère droit.
void arbre_ajouter_fils_courant(arbre a, void *val) {
  assert(a != NULL);
  assert(val != NULL);
  noeud_ajouter_fils(a->courant, val, a->copier);
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
  noeud noeudRecherche = noeud_rechercher(a->racine, val, est_egal);
  arbre arbreExtrait = NULL;
  if (noeudRecherche != NULL) {
    // Je créé un nouveau pointeur de struct_noeud (racine de arbre extrait),
    // j'y mets le contenu du pointeur vers le noeud recherché, et enfin je met
    // le pointeur vers le noeud recherché à NULL pour que l'arbre de base n'ai
    // plus de référence vers lui
    arbreExtrait = arbre_creer(a->copier, a->afficher, a->detruire);
    arbreExtrait->racine = (noeud)malloc(sizeof(struct noeud_struct));
    *(arbreExtrait->racine) = *noeudRecherche;
    noeudRecherche = NULL;
  }
  arbre_init_courant(arbreExtrait);
  arbre_init_courant(a);
  return arbreExtrait;
}
