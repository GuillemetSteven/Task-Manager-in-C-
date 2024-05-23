#ifndef UTILS_H
#define UTILS_H

#include <getopt.h>

extern struct option long_options[];

/**
 * @brief Affiche l'aide d'utilisation du programme.
 *
 * Cette fonction affiche les différentes options disponibles pour le programme,
 * ainsi que leur description.
 *
 * @param nom_programme Le nom du programme.
 */
void afficher_usage(char *nom_programme);

/**
 * @brief Vérifie si une chaîne de caractères représente un entier positif.
 *
 * Cette fonction vérifie si la chaîne de caractères passée en paramètre représente
 * un entier positif. Elle retourne 1 si c'est le cas, 0 sinon.
 *
 * @param chaine La chaîne de caractères à vérifier.
 * @return 1 si la chaîne représente un entier positif, 0 sinon.
 */
int verifier_entier_positif(char *chaine);

#endif
