# include "chaine.h"

# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include <ctype.h>


struct chaine {
  unsigned int taille ; 
  char * tab ; 
} ; 


chaine chaine_creer_vide ( ) { 
  return NULL ; 
}


chaine chaine_creer_char ( char * st ) { 
  return NULL ; 
}


void chaine_detruire ( chaine * ch ) { 
}


void chaine_afficher ( FILE * f , 
		       chaine ch ) { 
}

unsigned int chaine_extraire_taille ( chaine ch ) { 
  assert ( NULL != ch ) ; 
  return ch -> taille ;
}


bool chaine_est_vide ( chaine ch ) { 
  assert ( NULL != ch ) ; 
  return ( 0 == ch -> taille ) ; 
}

bool chaine_est_egal ( chaine ch1 , 
		       chaine ch2 ) { 
  return false ; 
}

void chaine_concatener ( chaine ch1 , 
			 chaine ch2 ) { 
}

char chaine_extraire_char_i ( chaine ch , 
			      const unsigned int i ) { 
  return 0 ; 
}

void chaine_modifier_char_i ( chaine ch , 
			      const unsigned int i , 
			      const char c ) {
  assert ( NULL != ch ) ; 
  assert ( i < ch -> taille ) ;
  ch -> tab[i] = c ; 
}

chaine chaine_copier ( chaine ch ) { 
  return NULL ; 
}

void chaine_en_minuscules ( chaine ch ) { 
  assert ( NULL != ch ) ; 
  if ( ! chaine_est_vide ( ch ) ) {
    for ( unsigned int i=0 ; i<ch -> taille ; i++ ) {
      ch -> tab[i]=toupper ( ch -> tab[i] ) ;
    }
  }
}

void chaine_en_majuscules ( chaine ch ) { 
  assert ( NULL != ch ) ; 
  if ( ! chaine_est_vide ( ch ) ) {
    for ( unsigned int i=0 ; i<ch -> taille ; i++ ) {
      ch -> tab[i]=toupper ( ch -> tab[i] ) ;
    }
  }
}


bool chaine_appartenir ( const char c , 
			 chaine ch , 
			 int * i ) { 
  return false ; 
}


chaine chaine_lire ( FILE * f , 
		     unsigned int taille ) { 
  return NULL ; 
}



