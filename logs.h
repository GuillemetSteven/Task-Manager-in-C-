#ifndef LOGS_H
#define LOGS_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Initialise le fichier de logs.
 *
 * Cette fonction ouvre le fichier de logs spécifié en mode "append" (ajout).
 * Si l'ouverture du fichier échoue, un message d'erreur est affiché et le
 * programme se termine.
 *
 * @param fichier Le chemin du fichier de logs.
 */
void initialiser_logs(const char *fichier);

/**
 * @brief Écrit un message de log dans le fichier de logs.
 *
 * Cette fonction écrit un message de log dans le fichier de logs, en incluant
 * l'horodatage et la commande associée.
 *
 * @param message Le message de log à écrire.
 * @param cmd La commande associée au message de log.
 */
void ecrire_log(const char *message, const char *cmd);

/**
 * @brief Ferme le fichier de logs.
 *
 * Cette fonction ferme le fichier de logs s'il a été ouvert précédemment.
 */
void fermer_logs();

#endif
