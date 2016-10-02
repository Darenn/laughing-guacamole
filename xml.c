#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#undef NDEBUG
#include "arbres.h"
#include "chaine.h"
#include "xml.h"

struct xml_struct {
  enum {ouvrante,fermante} type;
  chaine nom;
};

// A partir d'une chaine de caractères correspondant à une balise (<xxx> ou </xxx>) 
// on construit un xml avec ses deux champs nom et type.
xml xml_creer(char const* s)
{
}

// renvoie vrai si c'est une balise ouvrante
bool xml_est_ouvrante(xml x)
{
}

// renvoie vrai si c'est une balise fermante
bool xml_est_fermante(xml x)
{
}

// destruction d'un xml
void xml_detruire(xml* x)
{
}

// affichage (simplement le nom)
void xml_afficher(xml x, FILE* f)
{ 
}

// Les 4 fonctions ci-dessous sont usuels maintenant pour la manipulation d'un arbre d'xml...
void copier_xml(void* val, void** ptr)
{
}

void afficher_xml(void* val, FILE* f)
{
}

void detruire_xml(void** ptr)
{
}

bool est_egal_xml(void* val1, void* val2)
{
}


// Pour construire un arbre en lisant un fichier XML simple ne contenant qu'une serie de balises
// on supposera ce fichier bien formé au sens XML.
// Il peut etre nécessaire d'implémenter une fonction intermédiaire....
arbre xml_construction_arbre(char* source)
{
}

