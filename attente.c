#include "attente.h"

#include <stdio.h>
#include <unistd.h>

void attendre_prochain_exec(time_t start_time, int interval)
{
  // Obtenir l'heure actuelle
  time_t current_time;
  time(&current_time);

  // Calculer le temps écoulé depuis le début de l'exécution
  double elapsed_time = difftime(current_time, start_time);

  // Calculer le temps restant avant la prochaine exécution
  double actual_interval = interval - elapsed_time;

  // Si le temps restant est positif, attendre le temps restant
  if (actual_interval > 0)
  {
    printf("\n");
    printf("Temps d'attente avant la prochaine exécution : %f secondes\n", actual_interval);
    sleep(actual_interval);
  }
  // Sinon, exécuter la prochaine tâche immédiatement
  else
  {
    printf("Retard détecté, exécution immédiate de la prochaine tâche.\n");
  }
}