#ifndef ATTENTE_H
#define ATTENTE_H

#include <time.h>

/**
 * @brief Attend le temps nécessaire avant la prochaine exécution d'une tâche.
 *
 * @param start_time Le temps de début de la tâche, en secondes depuis l'époque.
 * @param interval L'intervalle en secondes entre chaque exécution de la tâche.
 */
void attendre_prochain_exec(time_t start_time, int interval);

#endif
