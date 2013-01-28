#ifndef DOCMYCODE_H
#define DOCMYCODE_H
#define MAX_LIGNES 426
#define TAILLE_TAB 300

void init_tab(char tab[MAX_LIGNES]);
int open_file(char *nom_fichier);
int display_tab(char tab[TAILLE_TAB],char *nom);
void special(char tab[TAILLE_TAB],char *nom);
void analyze_tab(char tab[TAILLE_TAB]);

#endif