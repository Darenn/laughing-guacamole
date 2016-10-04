# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <assert.h>
# include <ctype.h>

# undef NDEBUG

# include "arbre.h"
# include "chaine.h"
# include "xml.h"


struct balise_struct {
  enum { ouvrante , fermante } type ; 
  chaine nom ; 
} ; 



// A partir d'une chaîne de caractères correspondant à une balise ( <xxx> ou </xxx> ) 
// on construit un balise avec ses deux champs nom et type.
balise balise_creer ( char const * st ) { 
  return NULL ; 
}

// renvoie vrai si c'est une balise ouvrante
bool balise_est_ouvrante ( balise x ) { 
  assert ( x != NULL ) ; 
  return ( x -> type==ouvrante ) ; 
}

// renvoie vrai si c'est une balise fermante
bool balise_est_fermante ( balise x ) { 
  assert ( x != NULL ) ; 
  return ( x -> type==fermante ) ; 
}

// destruction d'un balise
void balise_detruire ( balise * x ) { 
}

// affichage ( simplement le nom ) 
static  void balise_afficher ( balise x , FILE * f ) { 
}

// Les 4 fonctions ci-dessous sont usuels maintenant pour la manipulation d'un arbre de balises...
static void copier_balise ( void * val , void * * ptr ) { 
}

void afficher_balise ( void * val , FILE * f ) { 
}

void detruire_balise ( void * * ptr ) { 
}

bool est_egal_balise ( void * val1 , void * val2 ) { 
  return true ;
}


// Retourne un pointeur sur le premier char qui n'est pas un espace et
// et met un 0 de manière à supprimer les derniers espaces.
static char * trim ( char  * st ) { 
  return NULL ; 
}



/* Pour construire un arbre en lisant un fichier XML simple ne contenant qu'une serie de balises */
/* on supposera ce fichier bien formé au sens XML. */
arbre xml_construction_arbre ( char * source ) { 
  return NULL ; 
}

