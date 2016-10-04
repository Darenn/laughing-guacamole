# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <assert.h>

# undef NDEBUG

# include "arbre.h"
# include "chaine.h"
# include "xml.h"


int main ( void ) 
{

  FILE * f_out = fopen ( "test_arbre_xml_out.txt" , "w" ) ; 
  arbre a = xml_construction_arbre ( "exemple_sujet.xml" ) ; 
  fprintf ( f_out , "-----------------Construction à partir du fichier exemple_sujet--------------\n" ) ; 
  arbre_afficher ( a , f_out , afficher_balise , "" ) ; 
 
  balise x = balise_creer ( "<fille1>" ) ; 
 
  arbre a_extrait = arbre_extraction ( a , x , est_egal_balise ) ; 

  fprintf ( f_out , "-----------------Test de l'extraction--------------\n" ) ; 
  fprintf ( f_out , "arbre extrait : \n" ) ; 
  arbre_afficher ( a_extrait , f_out  , afficher_balise , "" ) ; 

  fprintf ( f_out , "arbre restant : \n" ) ; 
  arbre_afficher ( a , f_out , afficher_balise , "" ) ; 
 
  arbre_detruire ( &a ) ; 
  arbre_detruire ( &a_extrait ) ; 
  balise_detruire ( &x ) ; 
  fclose ( f_out ) ; 

  return 0 ; 
}
