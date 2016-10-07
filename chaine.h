#ifndef CHAINE_H
#define CHAINE_H

#include <stdbool.h>
#include <stdio.h>

typedef struct chaine *chaine;

// Pour créer une chaine dont on ne connait pas la taille
// Ainsi pour la chaine vide tab pointe sur NULL et est de taille 0
chaine chaine_creer_vide();

// Pour créer une chaine à partir de c
chaine chaine_creer_char(char const *st);

// Pour désallouer correctement la mémoire
void chaine_detruire(chaine *ch);

// Pour afficher la chaîne dans un fichier au sens unix ( par exemple stdout )
// Le retour à la ligne est géré par chaine_afficher.
void chaine_afficher(FILE *f, chaine ch);

// Renvoie la taille de la chaîne de caractères
unsigned int chaine_extraire_taille(chaine ch);

// Renvoie vrai si la chaîne est vide
bool chaine_est_vide(chaine ch);
// Renvoie vrai si ch1 et ch2 sont identiques
bool chaine_est_egal(chaine ch1, chaine ch2);
// ch1 en sortie est la concaténation de ch1 et ch2
void chaine_concatener(chaine ch, chaine ch2);

// Renvoie le caractère à la position i de la chaîne ( on commence à compter à 0
// )
char chaine_extraire_char_i(chaine ch, const unsigned int i);
// Le caractère à la position i est modifié par le caractère c (la position doit
// être valide)
void chaine_modifier_char_i(chaine ch, const unsigned int i, const char c);

// Renvoie une chaîne contenant une copie de ch1
chaine chaine_copier(chaine ch1);

// Convertit une chaîne en minuscules
void chaine_en_minuscules(chaine ch);
// Convertit une chaîne en majuscules
void chaine_en_majuscules(chaine ch);

// Renvoie vrai si la chaîne ch contient le caractère c et i donne en plus la
// position de c dans ch
bool chaine_appartenir(const char c, chaine ch, int *i);

// Renvoie une chaîne par lecture de "taille" caractères sur un fichier au sens
// Unix ( par exemple stdin )
// ( sans faire de traitement particulier pour les caractères spéciaux ) .
chaine chaine_lire(FILE *f, unsigned int taille);

#endif
