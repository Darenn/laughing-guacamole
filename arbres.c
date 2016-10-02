#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#undef NDEBUG

#include "arbres.h"

struct noeud_struct {
  void* val;
  noeud pere;
  noeud filsgauche;
  noeud freredroit;
};

noeud noeud_creer_vide()
{
  noeud n = (noeud)malloc(sizeof(struct noeud_struct));
  n->val = NULL;
  n->pere = NULL;
  n->filsgauche = NULL;
  n->freredroit = NULL;
  return n;
}

noeud noeud_creer(void* val,void(*copier)(void* val, void**ptr))
{
  noeud n = (noeud)malloc(sizeof(struct noeud_struct));
  copier(val,&(n->val));
  n->pere = NULL;
  n->filsgauche = NULL;
  n->freredroit = NULL;
  return n;
}


void noeud_ajouter_filsgauche(noeud n, void* val, void(*copier)(void* val, void** ptr))
{
  assert(NULL!=n);

  noeud fg = noeud_creer(val,copier);
  fg->pere = n;
  fg->freredroit = n->filsgauche;
  n->filsgauche = fg;
}

void noeud_ajouter_freredroit(noeud n, void* val, void(*copier)(void* val, void** ptr))
{
  assert(NULL!=n);

  noeud fd = noeud_creer(val,copier);
  fd->pere = n->pere;
  while (n->freredroit!=NULL)
    n = n->freredroit;
  n->freredroit = fd;  
}

void noeud_ajouter_fils(noeud n, void* val, void(*copier)(void* val, void** ptr))
{
  assert(NULL!=n);

  if (n->filsgauche==NULL)
    noeud_ajouter_filsgauche(n,val,copier);
  else 
    noeud_ajouter_freredroit(n->filsgauche,val,copier);
}

void noeud_afficher(noeud n, void(*afficher)(void* val, FILE* f), FILE* f)
{
  if (n!=NULL) {
    afficher(n->val,f);
    noeud_afficher(n->filsgauche,afficher,f);
    noeud_afficher(n->freredroit,afficher,f);
  }
}

void noeud_detruire(noeud* n,void(detruire)(void** val))
{
  if ((*n)!=NULL) {
    noeud_detruire(&((*n)->filsgauche),detruire);
    noeud_detruire(&((*n)->freredroit),detruire);
    detruire(&((*n)->val));
    free(*n);
    *n = NULL;
  }
}


noeud noeud_rechercher(noeud n, void* val, bool(*est_egal)(void* val1, void* val2))
{
  if (n==NULL)
    return NULL;
  else {
    if (est_egal(n->val,val)) 
      return n;    
    else {
      noeud valg = noeud_rechercher(n->filsgauche,val,est_egal);
      if (valg!=NULL)
	return valg;
      else
	return noeud_rechercher(n->freredroit,val,est_egal);
    }
  }
}




struct arbre_struct {
  noeud racine; // pointe sur la racine de l'arbre (le noeud qui n'a pas de père)
  noeud courant; // permet de se déplacer dans l'arbre
  void (*copier)(void* val, void** pt);
  void (*afficher)(void* val, FILE* f);
  void (*detruire)(void** pt);
};

// la tete et courant sont à NULL
arbre arbre_creer(void (*_copier)(void* val, void** pt), void (*_afficher)(void* val, FILE* f), void (*_detruire)(void** pt))
{
}

// Destruction compléte de l'arbre
void arbre_detruire(arbre* a)
{
}

// Initialisation de courant à la tete de l'arbre
void arbre_init_courant(arbre a)
{
}

// On déplace courant sur son fils gauche
void arbre_courant_filsgauche(arbre a)
{
}

// On déplace courant sur son père
void arbre_courant_pere(arbre a)
{
}

// renvoie vrai si courant n'a pas de fils gauche
bool arbre_courant_sans_filsgauche(arbre a)
{
}

// On déplace courant sur son frere droit
void arbre_courant_freredroit(arbre a)
{
}

// affichage de l'arbre avec un passage à la ligne en fin
void arbre_afficher(arbre a, FILE* f)
{
}


// On insère une racine (nouvelle ou pas) à l'arbre
void arbre_inserer_racine(arbre a, void* val)
{
}

// On ajoute un fils gauche à partir de courant
// Si courant a déjà un fils gauche il devient un frère droit du nouveau fils gauche
void arbre_ajouter_filsgauche_courant(arbre a, void* val)
{
}

// On ajoute un frere droit à partir de courant
// rajouté à la fin des frères droits déjà existants
void arbre_ajouter_freredroit_courant(arbre a, void* val)
{
}

// On ajoute un fils soit comme fils gauche s'il n'existe pas
// soit comme un frère droit.
void arbre_ajouter_fils_courant(arbre a, void* val)
{
}

// on extrait l'arbre à partir du noeud n qui contient la valeur recherchée
// la fonction renvoie l'arbre dont la racine est n
// et l'arbre initial ne contient plus ce arbre extrait
// si la valeur n'existe pas on renvoie NULL
// courant doit etre initialisé à la racine dans les 2 cas.
arbre arbre_extraction(arbre a, void* val, bool(*est_egal)(void* val1, void* val2))
{
}


