#ifndef COMMANDE_H
#define COMMANDE_H

#include <errno.h>
#include <signal.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 10 // valeur arbitraire

extern volatile sig_atomic_t signal_recu;

/**
 * @brief Exécute une commande à intervalles réguliers.
 *
 * @param cmd La commande à exécuter.
 * @param interval L'intervalle en secondes entre chaque exécution de la commande.
 * @param iterations Le nombre de fois que la commande doit être exécutée.
 * @param output_file Le fichier dans lequel rediriger la sortie de la commande (peut être NULL).
 * @param exec_dir Le répertoire où se trouve l'exécutable de la commande (peut être NULL).
 * @param work_dir Le répertoire de travail dans lequel la commande doit être exécutée (peut être NULL).
 */
void amorcer(char *cmd, int interval, int iterations, const char *output_file, char *work_dir, char *exec_dir);

/**
 * @brief Prépare les arguments pour l'exécution d'une commande.
 *
 * @param cmd La commande à exécuter.
 * @param argv Un tableau qui contiendra les arguments de la commande.
 */
void preparer_commande(char *cmd, char *argv[]);

/**
 * @brief Exécute une commande de manière infinie avec un intervalle spécifié.
 *
 * @param cmd La commande à exécuter.
 * @param interval L'intervalle en secondes entre chaque exécution de la commande.
 * @param exec_dir Le répertoire où se trouve l'exécutable de la commande (peut être NULL).
 * @param work_dir Le répertoire de travail dans lequel la commande doit être exécutée (peut être NULL).
 */
void executer_en_mode_infini(char *cmd, int interval, char *exec_dir, char *work_dir);

#endif
