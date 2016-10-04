# ifndef __ARBRES_H
# define __ARBRES_H

# include <stdarg.h>
# include <stdbool.h>

/*!
 * \file
 * \brief Ce module permet de gérer des arbres généralisés génériques.
 *
 * Il est possible de parcourir un arbre et de s'y déplacer au moyen d'un type arbre_parcours
 *
 * Toutes les structures sont cachées dans le .c * 
 *
 * \copyright PASD
 * \version 2016
 */


/*!
 * Pointeur/référence permettant de manipuler des arbres.
 */
typedef struct arbre_struct * arbre ;


/*!
 * Référence une structure faite pour parcourir un arbre pas à pas (comme un itérateur).
 *
 * Attention, les positions des parcours ne sont pas mis-à-jour par les extractions de sous-arbre.
 */
typedef struct arbre_parcours_struct * arbre_parcours ; 


/*!
 * Pour engendrer un arbre généralisé générique vide. 
 * \param copier permet de copier une valeur (on ne donne pas l'endroit où mettre la valeur, mais l'endroit où renvoyer à cette valeur)
 * \param detruire sert à détruire une valeur.
 * \pre copier et detruire ne doivent pas être NULL
 * \return un arbre généralisé générique vide pour le type correspondant aux fonctions en paramètre.
 */
arbre arbre_creer ( void ( * copier ) ( void * val ,
					void * * pt ) , 
		    void ( * detruire ) ( void * * pt ) ) ; 


/*!
 * Détruit un arbre (et toutes les valeurs contenues)
 * \param a arbre à détruire
 * \pre a ne doit pas être NULL
 */
void arbre_detruire ( arbre * a ) ; 


/*!
 * Ajoute une racine à un arbre.
 * S'il y a déjà une racine, celle-ci devient son fils.
 * \param a arbre à afficher
 * \param val valeur à ajouter
 * \pre Ni a, ni val ne doivent être NULL
 */
void arbre_inserer_racine ( arbre a ,
			    void * val ) ; 




/*!
 * Affiche toutes les valeurs contenues dans un arbre selon un parcours préfixe.
 * Les valeurs sont séparées par sep.
 * Exemple :    24 :: 29 :: 15 :: 27 :: 21 :: 10 (avec sep valant " :: ")
 * \param a arbre à afficher
 * \param f flux où afficher
 * \param afficher fonction servant à afficher une valeur
 * \pre Ni a, ni f ni afficher ne doivent être NULL
 */
void arbre_afficher ( arbre a ,
		      FILE * f ,
		      void ( * afficher ) ( void * val ,
					    FILE * f )  ,
		      char const * const sep ) ; 


/*!
 * Affiche toutes les valeurs contenues dans un arbre selon un parcours préfixe avec en plus des parenthèses et des virgules pour montrer la structure abrorescente.
 * Exemple :   24 ( 29 , 15 ( 27 ( 21 ) , 10 ) )
 * \param a arbre à afficher
 * \param f flux où afficher
 * \param afficher fonction servant à afficher une valeur
 * \pre Ni a, ni f ni afficher ne doivent être NULL
 */
void arbre_afficher_tuple ( arbre a ,
			    FILE * f ,
			    void ( * afficher ) ( void * val ,
						  FILE * f ) ) ; 


/*!
 * Sert à extraire un sous-arbre.
 * Le sous-arbre recherché est le premier rencontré (avec un parcours préfixe) qui a la valeur recherchée comme racine.
 * la fonction renvoie l'arbre dont la racine est n et l'arbre initial ne contient plus cet arbre extrait.
 * \param a arbre d'où extraire
 * \param val valeur à chercher
 * \param est_egal fonction précisant le sens de l'égalité
 * \pre Ni a, ni val ni est_egal ne doivent être NULL
 * \return le sous-arbre extrait ou NULL si la valeur n'est pas contenue dans l'arbre.
 */
arbre arbre_extraction ( arbre a , 
			 void * val , 
			 bool ( * est_egal ) ( void * val1 ,
					       void * val2 ) ) ; 




/*
 * Retourne un parcours d'arbre.
 * Le parcours est sur le permier élément (s'il existe)
 * \param a arbre à parcourir
 * \pre a ne doit pas être NULL
 */
arbre_parcours arbre_creer_parcours ( arbre a ) ; 


/*
 * Détruit un parcours d'arbre.
 * L'arbre n'est pas modifié.
 * \param p parcours à détruire
 * \pre p ne doit pas être NULL
 */
void arbre_parcours_detruire ( arbre_parcours p ) ; 


/*!
 * Pour savoir si un parcours est terminé ou non
 * \param p parcour à tester
 * \pre p ne doit pas être NULL
 * \return vrai si le parcours est encore sur une valeur.
 */
bool arbre_parcours_est_fini ( arbre_parcours p ) ;


/*!
 * Passe à la position suivante du parcours.
 * On teste dans cet ordre
 * pour un fils
 * pour un frère
 * pour un frère d'un ancètre
 * \param p parcour à avancer d'une position
 * \pre p ne doit pas être NULL
 */
void arbre_parcours_suivant ( arbre_parcours p ) ;


/*!
 * Indique la valeur courante.
 * \param p parcour en cours
 * \pre p ne doit pas être NULL
 * \return la valeur à la position courante (sans copie).
 */
void * arbre_parcours_valeur ( arbre_parcours p ) ;


/*!
 * Pour savoir si la position courante a un fils
 * \param p parcour en cours
 * \pre p ne doit pas être fini
 * \return true s'il a un fils 
 */
bool arbre_parcours_a_fils ( arbre_parcours p ) ; 


/*!
 * On déplace position courante sur son fils le plus à gauche
 * \param p parcour en cours
 * \pre p ne doit pas être fini
 * \pre il doit y avoir un fils 
 */
void arbre_parcours_aller_fils_gauche ( arbre_parcours p ) ; 


/*!
 * On déplace position courante sur son fils le plus à droite
 * \param p parcour en cours
 * \pre p ne doit pas être fini
 * \pre il doit y avoir un fils 
 */
void arbre_parcours_aller_fils_droite ( arbre_parcours p ) ; 


/*!
 * Pour savoir si la position courante a un frere droit
 * \param p parcour en cours
 * \pre p ne doit pas être fini
 * \return true s'il a un frere droit
 */
bool arbre_parcours_a_frere_droit ( arbre_parcours p ) ; 


/*!
 * On déplace la position courante sur son frere droit le plus à gauche
 * \param p parcour en cours
 * \pre p ne doit pas être fini
 * \pre il doit y avoir un frere droit
 */
void arbre_parcours_aller_frere_droit ( arbre_parcours p ) ; 


/*!
 * Pour savoir si la position courante a un père
 * \param p parcour en cours
 * \pre p ne doit pas être fini
 * \return true s'il a un père
 */
bool arbre_parcours_a_pere ( arbre_parcours p ) ; 


/*!
 * On déplace la position courante sur son père
 * \param p parcour en cours
 * \pre p ne doit pas être fini
 * \pre il doit y avoir un père
 */
void arbre_parcours_aller_pere ( arbre_parcours p ) ; 


/*!
 * Ajoute un frere complètement à droite à partir de la position courante
 * \param p parcour en cours
 * \pre p ne doit pas être fini
 * \pre val ne doit pas être NULL
 */
void arbre_parcours_ajouter_frere_a_droite ( arbre_parcours p ,
					     void * val ) ; 


/*!
 * Ajoute un fils complètement à gauche de tous les autres à partir de la position courante
 * \param p parcour en cours
 * \pre p ne doit pas être fini
 * \pre val ne doit pas être NULL
 */
void arbre_parcours_ajouter_fils_a_gauche ( arbre_parcours p ,
					    void * val ) ; 


/*!
 * Ajoute un fils complètement à droite de tous les autres à partir de la position courante
 * \param p parcour en cours
 * \pre p ne doit pas être fini
 * \pre val ne doit pas être NULL
 */
void arbre_parcours_ajouter_fils_a_droite ( arbre_parcours p ,
					    void * val ) ; 


/*!
 * Permet de faire un même traitement à toutes les valeurs dans l'arbre.
 * Les valeurs sont parcourus dans l'ordre prefix.
 * Les arguments complémentaires sont répercutés à faire à chaque fois.
 * \param a arbre à parcourir
 * \param faire
 * \param ... arguments complémentaires
 * \pre p et action ne doivent pas être NULL
 */
void arbre_parcourir ( arbre a ,
		       void ( * faire ) ( void * val1 ,
					  va_list args ) ,
		       ... ) ;



# endif
