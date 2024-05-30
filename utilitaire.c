//
// Created by stephane on 04/05/24.
//

#define _CRT_SECURE_NO_WARNINGS
#include "utilitaire.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Ouverture en lecture du fichier dont le nom est passe en parametre
 * @param nomFichier : nom du fichier a ouvrir en lecture
 * @return le descripteur de fichier representant le fichier nouvellement ouvert
 */
Fichier fichierOuvrirLecture(Chaine nomFichier) {
    FILE *f = fopen(nomFichier, "r");
    if (!f) {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier %s en lecture dans fichierOuvrirLecture", nomFichier);
        exit(EXIT_FAILURE);
    }
    return f;
}

/**
 * @brief Ouverture en ecriture du fichier dont le nom est passe en parametre
 * @param nomFichier : nom du fichier a ouvrir en ecriture
 * @return le descripteur de fichier representant le fichier nouvellement ouvert
 */
Fichier fichierOuvrirEcriture(Chaine nomFichier) {
    FILE *f = fopen(nomFichier, "w");
    if (!f) {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier %s en ecriture dans fichierOuvrirEcriture",
                nomFichier);
        exit(EXIT_FAILURE);
    }
    return f;
}

/**
 * @brief Ferme le fichier passe en parametre
 * @param fichier : fichier a fermer
 * @endcode EXIT_FAILURE si la fermeture a echouee
 */
void fichierFermer(Fichier fichier) {
    if (fclose(fichier) == EOF) {
        fprintf(stderr, "Erreur : impossible de fermer le fichier dans fichierFermer");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Teste si on est arrive a la fin d'un fichier
 * @param fichier : le fichier a tester
 * @return true si la fin du fichier a ete atteinte, false sinon
 */
bool finDeFichier(Fichier fichier) {
    int c = fgetc(fichier);
    if (c == EOF) return true;
    ungetc(c, fichier);
    return false;
}

/**
 * @brief Lire la prochaine chaine de caracteres dans un fichier
 * @param fichier : le fichier a lire
 * @param chaine : la chaine sera deposee ici apres lecture
 * @return true si une chaine a ete lue, false si fin de fichier atteinte
 */
bool fichierLireChaine(Fichier fichier, Chaine chaine) {
    return fscanf(fichier, "%s", chaine) != EOF;
}

/**
 * @brief Ecrire une chaine de caractere dans un fichier
 * @param fichier : le fichier qui sera ecrit
 * @param chaine : la chaine a ecrire dans le fichier
 * @endcode EXIT_FAILURE si aucune chaine n'a pu etre ecrite
 */
void fichierEcrireChaine(Fichier fichier, Chaine chaine) {
    int r = fprintf(fichier, "%s", chaine);
    if (r < 0) {
        fprintf(stderr, "Erreur : ecriture d'une chaine de caracteres dans fichierEcrireChaine");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Se positionne sur la prochaine ligne du fichier si possible.
 * @param fichier : le fichier dans lequel on veut avancer d'une ligne
 * @return true si la fonction a reussi, false si elle a echouee
 */
bool fichierLigneSuivante(Fichier fichier) {
    bool fin = false;
    while (!fin) {
        int c = fgetc(fichier);
        if (c == EOF) return false;
        fin = (c == '\n');
    }
    return true;
}

/**
 * @brief Teste si 2 villes sont identiques
 * @param ville1 : premiere ville
 * @param ville2 : deuxieme ville
 * @return true si les 2 villes sont les memes, false sinon
 */
bool chainesEgales(Chaine ville1, Chaine ville2) {
    return strcmp(ville1, ville2) == 0;
}

/**
 * @brief Copie une chaine dans une autre
 * @param source : la chaine qui sera copiee
 * @param destination : la chaine qui recevra la copie
 */
void chainesCopier(Chaine source, Chaine destination) {
    strcpy(destination, source);
}

/**
 * @brief Convertit un entier en une chaine de caracteres
 * @param n : l'entier a convertir
 * @param chaine : la chaine dans laquelle deposer le resultat de la conversion
 * @return true si la conversion a ete possible, false sinon
 */
bool entierVersChaine(int n, Chaine chaine) {
    return (sprintf(chaine, "%d", n) != 0);
}

/**
 * @brief Convertit un reel en une chaine de caracteres
 * @param n : le reel a convertir
 * @param c : la chaine dans laquelle deposer le resultat de la conversion
 * @return true si la conversion a ete possible, false sinon
 */
bool reelVersChaine(double x, Chaine c) {
    return (sprintf(c, "%lf", x) != 0);
}