#ifndef GESTION_SIGNAUX_H
#define GESTION_SIGNAUX_H

/**
 * @brief Gestionnaire de signal pour le signal SIGINT (Ctrl+C).
 *
 * Cette fonction est appelée lorsque le signal SIGINT (envoyé par Ctrl+C) est
 * reçu. Elle met à jour la variable `signal_recu` pour indiquer que le signal
 * a été reçu, et affiche un message indiquant que le mode infini a été
 * désactivé.
 *
 * @param signal Le numéro du signal reçu (dans ce cas, SIGINT).
 */
void gestionnaire_signal(int signal);

/**
 * @brief Configure le gestionnaire de signal pour le signal SIGINT (Ctrl+C).
 *
 * Cette fonction configure un gestionnaire de signal qui sera appelé lorsque le
 * signal SIGINT (envoyé par Ctrl+C) sera reçu. Le gestionnaire
 * de signal met à jour la variable `signal_recu` pour indiquer que le signal a
 * été reçu.
 */
void configurer_gestionnaire_signal();

#endif
