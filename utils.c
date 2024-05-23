#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

// Tableau des options en ligne de commande
struct option long_options[] = {
    {"command", required_argument, 0, 'c'},
    {"interval", required_argument, 0, 'i'},
    {"iterations", required_argument, 0, 'n'},
    {"infinite", no_argument, 0, 'f'},
    {"exec-dir", required_argument, 0, 'e'},
    {"work-dir", required_argument, 0, 'w'},
    {"output", required_argument, 0, 'o'},
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}};

void afficher_usage(char *nom_programme)
{
  // Affichage de l'aide sur l'utilisation du programme
  printf("Usage: %s [options]\n", nom_programme);
  printf("Options:\n");
  printf("  -c, --command <commande>          Commande à exécuter\n");
  printf("  -i, --interval <intervalle>       Intervalle de temps (en secondes) entre les exécutions\n");
  printf("  -n, --iterations <iterations>     Nombre d'itérations\n");
  printf("  -f, --infinite                    Exécuter la commande indéfiniment (CTRL+C pour arrêter)\n");
  printf("  -o, --output <fichier>            Rediriger la sortie standard vers un fichier\n");
  printf("  -w, --work-dir <répertoire>       Définir le répertoire de travail pour l'exécution de la commande\n");
  printf("  -e, --exec-dir <répertoire>       Définir le répertoire contenant l'exécutable de la commande\n");
  printf("  -h, --help                        Afficher cette aide et quitter\n");
}

int verifier_entier_positif(char *chaine)
{
  // Vérification que la chaîne représente un entier positif
  char *fin = NULL;
  long valeur = strtol(chaine, &fin, 10);

  if (*fin != '\0' || valeur <= 0)
  {
    return 0;
  }

  return 1;
}
