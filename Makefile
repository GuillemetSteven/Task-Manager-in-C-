# Compilation des fichiers source en fichiers objet
main.o: main.c utils.h commandes.h gestion_signaux.h logs.h
	gcc -c main.c -Wall -Wextra 

utils.o: utils.c utils.h
	gcc -c utils.c -Wall -Wextra 

commandes.o: commandes.c commandes.h attente.h
	gcc -c commandes.c -Wall -Wextra 

attente.o: attente.c attente.h
	gcc -c attente.c -Wall -Wextra 

logs.o: logs.c logs.h
	gcc -c logs.c -Wall -Wextra 

gestion_signaux.o: gestion_signaux.c gestion_signaux.h
	gcc -c gestion_signaux.c -Wall -Wextra 

# Lier les fichiers objet pour créer l'exécutable
main.exe: main.o utils.o commandes.o attente.o logs.o gestion_signaux.o
	gcc -o main.exe main.o utils.o commandes.o attente.o logs.o gestion_signaux.o -Wall -Wextra

# Nettoyer les fichiers compilés
clean:
	rm -f *.o main.exe taches.log *.txt

# Construire l'exécutable
all: main.exe
