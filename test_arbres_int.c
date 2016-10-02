#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#undef NDEBUG
#include "arbres.h"

#define LG 10



void copier_int(void* val, void** pt)
{
  *pt = (int*)malloc(sizeof(int));
  memcpy(*pt,val,sizeof(int));
}

void afficher_int(void* val, FILE* f)
{
  fprintf(f,"%d ",*((int*)(val)));
}

void detruire_int(void **pt)
{
  if (*pt != NULL) {
    free(*pt);
    (*pt) = NULL;
  }
}

bool est_egal_int(void* val1, void* val2)
{
  int a = *(int*)val1;
  int b = *(int*)val2;
  return(a==b);
}

int main (void)
{
  arbre a = arbre_creer(copier_int,afficher_int, detruire_int);

  srand(1234);

  int val = rand()%30;
  printf("racine = %d \n",val);
  arbre_inserer_racine(a,&val);

  arbre_init_courant(a);
  for (int i=0; i<LG; i++) {
    val=rand()%30;
    printf("insérer = %d \n",val);
    if (i%2==0) {
      arbre_ajouter_filsgauche_courant(a,&val);
      arbre_courant_filsgauche(a);
    }
    else if (i%3==0) 
      arbre_ajouter_freredroit_courant(a,&val);
    else {
      arbre_ajouter_freredroit_courant(a,&val);
      arbre_courant_freredroit(a);
    }
  }
  arbre_afficher(a,stdout);
  
  val = 25;
  arbre a_extrait = arbre_extraction(a,&val,est_egal_int);
  
  printf("arbre extrait : ");
  arbre_afficher(a_extrait,stdout);
  
  printf("arbre restant : ");
  arbre_afficher(a,stdout);
  
  
  arbre_detruire(&a);
  arbre_detruire(&a_extrait);
  

  return 0 ;
}
