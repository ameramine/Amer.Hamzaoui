// Ce programme simule le jeu de papier-caillou-ciseaux. Le joueur peut jouer contre l'ordinateur ou bien avec un ami
// realise par Hamzaoui mehdi et Amer Mohammed Amine 



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Fonction pour obtenir le choix du joueur
int choixJoueur(char nomJoueur[]) {
    int choix;
    printf("%s, choisissez une option :\n", nomJoueur);
    printf("1. Pierre\n");
    printf("2. Papier\n");
    printf("3. Ciseaux\n");
    printf("Votre choix : ");
    scanf("%d", &choix);
    return choix;
}

// Fonction pour générer le choix de l'ordinateur
int genererChoixOrdinateur() {
    return rand() % 3 + 1;  // Génère un choix aléatoire entre 1 et 3
}

// Fonction pour afficher le résultat du jeu
void afficherResultat(char nomJoueur1[], char nomJoueur2[], int choixJoueur1, int choixJoueur2, int *scoreJoueur1, int *scoreJoueur2) {
    if (choixJoueur1 == choixJoueur2) {
        printf("Egalite !\n");
    } else if ((choixJoueur1 == 1 && choixJoueur2 == 3) ||
               (choixJoueur1 == 2 && choixJoueur2 == 1) ||
               (choixJoueur1 == 3 && choixJoueur2 == 2)) {
        printf("%s gagne !\n", nomJoueur1);
        (*scoreJoueur1)++;
    } else {
        printf("%s gagne !\n", nomJoueur2);
        (*scoreJoueur2)++;
    }
}
// Fonction pour enregistrer les scores dans un fichier
void enregistrerScore(char* Nom, int score) {
    FILE* fichier = fopen("scores.txt", "a");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }

    fprintf(fichier, "Nom: %s, Score: %d\n", Nom, score);

    fclose(fichier);
}
// Fonction pour lire les anciens scores depuis un fichier
void lireAnciensScores() {
    FILE* fichier = fopen("scores.txt", "r");

    if (fichier == NULL) {
        // Le fichier n'existe pas encore, pas besoin de lire les anciens scores
        return;
    }

    printf("Anciens Scores :\n");

    char ligne[100];
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        printf("%s", ligne);
    }

    fclose(fichier);

    // Effacer le contenu du fichier
    fichier = fopen("scores.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'effacement du fichier.\n");
        exit(1);
    }
    fclose(fichier);
}

int main() {
    srand(time(NULL));  // Initialiser aléatoire
    lireAnciensScores();
    int nombreJoueurs, choixJoueur1, choixJoueur2, tours;
    char nomJoueur1[50], nomJoueur2[50];
    int scoreJoueur1 = 0, scoreJoueur2 = 0;
	printf("\nJeu de Pierre,Papier,Ciseaux \n\n");
    printf("1.Jouer avec l'ordinateur \n");
    printf("2.Jouer avec un ami \n");
    printf("Votre choix : ");
    scanf("%d", &nombreJoueurs);
	printf("*************************\n");
    if (nombreJoueurs != 1 && nombreJoueurs != 2) {
        printf("Nombre de joueurs invalide.\n");
        return 1;
    }

    printf("Entrez le nom du Joueur 1 : ");
    scanf("%s", nomJoueur1);

    if (nombreJoueurs == 2) {
        printf("Entrez le nom du Joueur 2 : ");
        scanf("%s", nomJoueur2);
    } else {
        // Affecter une nouvelle valeur à nomJoueur2 avec strcpy
        strcpy(nomJoueur2, "l'ordinateur");
    }

    printf("Entrez le nombre de tours : ");
    scanf("%d", &tours);

    int tour;
    for (tour = 1; tour <= tours; ++tour) {
    	printf("*************************");
        printf("\nTour %d\n", tour);
        printf("*************************\n");

        choixJoueur1 = choixJoueur(nomJoueur1);

        if (nombreJoueurs == 1) {
            choixJoueur2 = genererChoixOrdinateur();
        } else {
            choixJoueur2 = choixJoueur(nomJoueur2);
        }

        printf("%s a choisi : %d\n", nomJoueur1, choixJoueur1);
        if (nombreJoueurs == 2) {
            printf("%s a choisi : %d\n", nomJoueur2, choixJoueur2);
        }

        afficherResultat(nomJoueur1, nomJoueur2, choixJoueur1, choixJoueur2, &scoreJoueur1, &scoreJoueur2);
        printf("        Scores : %s: %d, %s: %d\n", nomJoueur1, scoreJoueur1, nomJoueur2, scoreJoueur2);
    }
    enregistrerScore(nomJoueur1, scoreJoueur1);
    enregistrerScore(nomJoueur2, scoreJoueur2);
    return 0;
}
