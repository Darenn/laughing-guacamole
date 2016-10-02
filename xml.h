#ifndef XML
#define XML


typedef struct xml_struct* xml;

xml xml_creer(char* s);
bool xml_est_ouvrante(xml x);
bool xml_est_fermante(xml x);
void xml_detruire(xml* x);
void xml_afficher(xml x, FILE* f);

void copier_xml(void* val, void** ptr);
void afficher_xml(void* val, FILE* f);
void detruire_xml(void** ptr);
bool est_egal_xml(void* val1, void* val2);

void xml_construction(arbre a, FILE* f);
arbre xml_construction_arbre(char* source);
#endif
