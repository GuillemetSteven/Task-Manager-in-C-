#include "logs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static FILE *fichier_log = NULL;

void initialiser_logs(const char *fichier)
{
  // Ouvre le fichier de log en mode "append"
  fichier_log = fopen(fichier, "a");
  if (!fichier_log)
  {
    perror("Erreur lors de l'ouverture du fichier de log");
    exit(EXIT_FAILURE);
  }
}

void ecrire_log(const char *message, const char *cmd)
{
  // Obtenir l'heure actuelle
  time_t now = time(NULL);
  char *timestamp = ctime(&now);
  timestamp[strlen(timestamp) - 1] = '\0'; // Supprimer le saut de ligne

  // Ouvrir le fichier de log en mode "append"
  FILE *log_file = fopen("taches.log", "a");
  if (log_file == NULL)
  {
    perror("Impossible d'ouvrir le fichier de log");
    return;
  }

  // Écrire le message de log dans le fichier
  fprintf(log_file, "[%s] %s : %s\n", timestamp, cmd, message);
  fclose(log_file);
}

void fermer_logs()
{
  // Fermer le fichier de log s'il est ouvert
  if (fichier_log)
  {
    fclose(fichier_log);
    fichier_log = NULL;
  }
}
