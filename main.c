#include "utils.h"
#include "commandes.h"
#include "gestion_signaux.h"
#include "logs.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <getopt.h>
#include <time.h>
#include <limits.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 10 // Limite arbitraire pour les arguments

extern volatile sig_atomic_t signal_recu;

int main(int argc, char *argv[])
{
  printf("\n");
  char cmd[MAX_CMD_LEN] = "";
  int interval = 1;   // Exécution immédiate si non spécifié
  int iterations = 1; // Exécuter une seule fois si non spécifié
  int option_index = 0;
  int c;
  int infinite = 0;
  const char *output_file = NULL;
  char *exec_dir = NULL; // Répertoire de l'exécutable
  char *work_dir = NULL; // Répertoire de travail

  // Parsing des options de ligne de commande
  while ((c = getopt_long(argc, argv, "c:i:n:o:fe:w:h", long_options, &option_index)) != -1)
  {
    switch (c)
    {
    case 'c':
      strncpy(cmd, optarg, MAX_CMD_LEN - 1);
      cmd[MAX_CMD_LEN - 1] = '\0';
      break;
    case 'i':
      interval = verifier_entier_positif(optarg) ? atoi(optarg) : interval;
      break;
    case 'n':
      iterations = verifier_entier_positif(optarg) ? atoi(optarg) : iterations;
      break;
    case 'f':
      infinite = 1;
      break;
    case 'o':
      output_file = optarg;
      break;
    case 'e':
      exec_dir = optarg;
      break;
    case 'w':
      work_dir = optarg;
      break;
    case 'h':
      afficher_usage(argv[0]);
      return EXIT_SUCCESS;
    }
  }

  // Vérifier que la commande est spécifiée
  if (strlen(cmd) == 0)
  {
    fprintf(stderr, "Le paramètre command est obligatoire.\n\n");
    afficher_usage(argv[0]);
    return EXIT_FAILURE;
  }

  // Configurer le gestionnaire de signal et initialiser les logs
  configurer_gestionnaire_signal();
  initialiser_logs("taches.log");

  // Exécuter la commande en mode infini ou en mode itératif
  if (infinite)
    executer_en_mode_infini(cmd, interval, exec_dir, work_dir);
  else
    amorcer(cmd, interval, iterations, output_file, work_dir, exec_dir);

  // Fermer les logs et quitter
  fermer_logs();
  return EXIT_SUCCESS;
}