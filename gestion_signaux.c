#include "gestion_signaux.h"

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

volatile sig_atomic_t signal_recu = 0;

void gestionnaire_signal(int signal)
{
  (void)signal;    // Supprime l'avertissement sur le paramètre inutilisé
  signal_recu = 1; // Indique que le signal a été reçu
  const char *msg_désactivé = "Mode infini désactivé.\n";
  write(STDOUT_FILENO, msg_désactivé, strlen(msg_désactivé));
  // Affiche le message de désactivation
}

void configurer_gestionnaire_signal()
{
  // Configuration du gestionnaire de signal pour le signal SIGINT (Ctrl+C)
  struct sigaction action;
  action.sa_handler = gestionnaire_signal; // Fonction à appeler lors de la réception du signal
  sigemptyset(&action.sa_mask);            // Masque vide (aucun autre signal bloqué)
  action.sa_flags = 0;                     // Pas de drapeau particulier

  if (sigaction(SIGINT, &action, NULL) < 0)
  {
    perror("Erreur lors de la configuration du gestionnaire de signal");
    exit(EXIT_FAILURE);
  }
}
