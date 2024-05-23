#include "commandes.h"
#include "attente.h"
#include "logs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>

void preparer_commande(char *cmd, char *argv[])
{
  char *token;
  int index = 0;

  // Découper la commande en tokens séparés par des espaces
  token = strtok(cmd, " "); // Premier token
  while (token != NULL)
  {
    argv[index++] = token;
    token = strtok(NULL, " "); // Prochains tokens
  }
  argv[index] = NULL; // Terminer par NULL pour execv
}

void amorcer(char *cmd, int interval, int iterations, const char *output_file, char *work_dir, char *exec_dir)
{
  char *argv[MAX_ARGS];
  char cmd_copy[MAX_CMD_LEN];

  pid_t pid = fork();
  if (pid == -1)
  {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  else if (pid > 0)
  {
    // Le processus parent se termine
    exit(EXIT_SUCCESS);
  }

  // Le processus enfant continue
  if (setsid() == -1)
  {
    perror("setsid");
    exit(EXIT_FAILURE);
  }

  // Fermeture des descripteurs de fichiers standard
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  for (int i = 0; i < iterations; ++i)
  {
    // Heure de début
    time_t start_time;
    time(&start_time);

    // Journalisation du début
    ecrire_log("Exécution de la tâche...", cmd);

    // Exécution de la commande dans un processus enfant
    pid_t cpid = fork();
    if (cpid == -1)
    {
      perror("fork");
      exit(EXIT_FAILURE);
    }
    else if (cpid == 0)
    {
      // Préparation de la commande et des arguments
      strncpy(cmd_copy, cmd, MAX_CMD_LEN);
      preparer_commande(cmd_copy, argv);

      // Redirection de la sortie si spécifiée
      if (output_file)
      {
        freopen(output_file, "a", stdout);
        freopen(output_file, "a", stderr);
      }

      // Changement du répertoire de travail si spécifié
      if (work_dir != NULL && chdir(work_dir) != 0)
      {
        perror("chdir failed");
        exit(EXIT_FAILURE);
      }

      // Définition du chemin complet de l'exécutable si spécifié
      if (exec_dir != NULL)
      {
        char full_cmd_path[PATH_MAX];
        snprintf(full_cmd_path, sizeof(full_cmd_path), "%s/%s", exec_dir, argv[0]);
        argv[0] = full_cmd_path;
      }

      execv(argv[0], argv);
      perror("execv failed");
      exit(EXIT_FAILURE);
    }
    else
    {
      // Attente de la fin du processus enfant
      waitpid(cpid, NULL, 0);
      attendre_prochain_exec(start_time, interval);
    }

    ecrire_log("Fin de l'exécution de la tâche.", cmd);
  }

  exit(EXIT_SUCCESS);
}

void executer_en_mode_infini(char *cmd, int interval, char *exec_dir, char *work_dir)
{
  const char *msg_activé = "Mode infini activé. Appuyez sur CTRL+C pour arrêter.\n";
  write(STDOUT_FILENO, msg_activé, strlen(msg_activé)); // Affiche le message immédiatement

  // Exécution de la tâche en mode infini
  while (!signal_recu)
  {
    ecrire_log("Exécution de la tâche en mode infini...", cmd);
    pid_t pid = fork();
    if (pid == -1)
    {
      perror("fork");
      exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
      // Processus enfant
      char *argv_exec[MAX_ARGS];
      preparer_commande(cmd, argv_exec);

      // Définition du chemin complet de l'exécutable si nécessaire
      if (exec_dir != NULL)
      {
        char *exec_path = exec_dir;
        // Supprimer le slash final si présent
        if (exec_path[strlen(exec_path) - 1] == '/')
        {
          exec_path[strlen(exec_path) - 1] = '\0';
        }

        char full_cmd_path[PATH_MAX];
        snprintf(full_cmd_path, sizeof(full_cmd_path), "%s/%s", exec_path, argv_exec[0]);
        argv_exec[0] = full_cmd_path;
      }

      // Exécuter la commande dans le répertoire de travail spécifié
      if (work_dir != NULL)
      {
        if (chdir(work_dir) != 0)
        {
          perror("chdir failed");
          exit(EXIT_FAILURE);
        }
      }

      execv(argv_exec[0], argv_exec);
      fprintf(stderr, "Erreur lors de l'exécution de %s: %s\n", argv_exec[0], strerror(errno));
      exit(EXIT_FAILURE);
    }
    else
    {
      // Processus parent
      int status;
      waitpid(pid, &status, 0);
    }

    sleep(interval);
  }

  ecrire_log("Arrêt demandé. Fin de l'exécution.", cmd);
}
