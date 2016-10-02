#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#undef NDEBUG
#include "arbres.h"
#include "chaine.h"
#include "xml.h"

int main (void)
{

  arbre a = xml_construction_arbre("exemple_sujet.xml");  
  arbre_afficher(a,stdout);

  xml x = xml_creer("<fille1>");
  
  arbre a_extrait = arbre_extraction(a,x,est_egal_xml);
  
  printf("arbre extrait : \n");
  arbre_afficher(a_extrait,stdout);

  printf("arbre restant : \n");
  arbre_afficher(a,stdout);

  
  arbre_detruire(&a);
  arbre_detruire(&a_extrait);
  xml_detruire(&x);

  return 0 ;
}
