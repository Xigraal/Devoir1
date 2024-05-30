//
// Created by stephane on 04/05/24.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utilitaire.h"
#include "structures.h"
#include "constantes.h"

//  Fonctions 1 et 2 : affichage d'une duree et test d'egalite de 2 villes
//  ----------------------------------------------------------------------

/**
 * @brief Affiche une duree donnees en decimales, en heures et minutes
 * @param duree : le temps en heures a afficher
 * @example affichera 3h15' pour une duree de 3.25. Ou encore 1h20' pour une duree de 1.33
 * @note Fonction 1
 */
void afficherDuree(double duree) {

    int part_entiere ; // variable qui contient la valeur en heure
    double part_decimale; //variable qui contient la valeur des minutes et secondes en decimale
    int minutes; // variable qui contient les valeurs decimales en minutes
    
    part_entiere = duree; // recupperation de la valeur en heure
    part_decimale = duree - part_entiere; //recupperation de la valeur des minutes
    minutes = (part_decimale * MINUTES_DANS_UNE_HEURE) + FACTEUR_DE_CORRECTION; // convertir les valeurs decimales en minutes

    printf(" %dh%d\n", part_entiere, minutes);
}

/**
 * @brief Teste si 2 villes sont egales
 * @param ville1 : la premiere ville
 * @param ville2 : la seconde ville
 * @return true si les 2 villes sont les memes, false sinon
 * @note Fonction 2
 */
bool villesEgales(Chaine ville1, Chaine ville2) {

    if(chainesEgales(ville1, ville2)){
        return true;
    }
    else {
        return false;
    }
}

//  Fonctions 3 a 6 : deplacement dans un fichier
//  ---------------------------------------------

/**
 * @brief Lit et retourne le prochain entier dans un fichier. On ne doit pas se trouver a la fin du fichier.
 * @param fichier : le fichier dans lequel l'entier doit etre lu
 * @return l'entier lu dans le fichier
 * @endcode EXIT_FAILURE si la fin de fichier a ete atteinte
 * @note Fonction 3
 */
int fichierLireEntier(Fichier fichier) {

    Chaine chaine;
    
    if (finDeFichier(fichier)) {

        fprintf(stderr, "Erreur: la fin de fichier a ete atteinte\n");
        exit(EXIT_FAILURE);
    }

    bool valide = fichierLireChaine(fichier, chaine);

    if (valide) {
        return atoi(chaine);
    }
    else {
        fprintf(stderr, "Erreur de lecture du fichier");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Lit et retourne le prochain reel dans un fichier. On ne doit pas se trouver a la fin du fichier.
 * @param fichier : le fichier dans lequel le reel doit etre lu
 * @return le reel lu dans le fichier
 * @endcode EXIT_FAILURE si la fin de fichier a ete atteinte
 * @note Fonction 4
 */
double fichierLireReel(Fichier fichier) {

	Chaine chaine;

	bool valide = fichierLireChaine(fichier, chaine);

	if (valide) {
		return atof(chaine);
	}
	else {
		printf("Erreur de lecture du fichier");
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief Avance de n champs dans le fichier, si c'est possible
 * @param fichier : le fichier dans lequel il faut avancer
 * @param n : le nombre de champs a sauter
 * @return true si succes, false sinon
 * @note Fonction 5
 */
bool fichierAvancerChamps(Fichier fichier, int n) {

    int i = 0;
    Chaine chaine;

    while (i < n && fichierLireChaine(fichier, chaine)) {
        i++;
    }
    if (i == n) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * @brief Avance d'un certain nombre de lignes dans un fichier
 * @param fichier : le fichier dans lequel avancer
 * @param n : le nombre de lignes a sauter
 * @return true si succes, false sinon
 * @note Fonction 6
 */
bool fichierAvancerLignes(Fichier fichier, int n) {

    for (int i = 0; i < n; i++) {

        if (!fichierLigneSuivante(fichier)) {
            return false; // Echec de l'avancement des lignes, car la fin de fichier a ete atteinte
        }
    }

    return true; // Succes de l'avancement des lignes
}

//  Fonctions 7 a 10 : manipulation des villes
//  ------------------------------------------

/**
 * @brief Recherche le numero de ligne du fichier de distances qui contient une ville
 * @param ville : la ville recherchee
 * @return le numero de la ligne ou se trouve les donnees relatives a la ville, ou -1 si la ville n'a pas ete trouvee
 * @note Fonction 7
 */
int chercherNumeroVille(Chaine ville) {
    
    int numero_de_ligne = 0;
    Fichier fichier;
    Chaine ligne;

    fichier = fichierOuvrirLecture(FICHIER_DES_DISTANCES);
    while (!finDeFichier(fichier)) {

        numero_de_ligne++;

        if (!fichierLireChaine(fichier, ligne)) {
            fprintf(stderr, "Erreur de lecture du fichier\n");
            fichierFermer(fichier); // ferme le fichier car le numero n'a pas ete trouve
            exit(EXIT_FAILURE);
        }
        if (strstr(ligne, ville) != NULL) {
            fichierFermer(fichier); // ferme le fichier car le numero a ete trouve
            return numero_de_ligne;
        }
        if (!fichierLigneSuivante(fichier)) {
            break; // Arrêter la recherche si la fin du fichier est atteinte
        }
    }

    fichierFermer(fichier);
    return -1; // La ville n'a pas été trouvée

    }

/**
 * @brief Cherche une ville dans la liste des villes a partir de son numero
 * @param numeroVille : le numero de la ville dans le fichier des villes
 * @param ville : la ville trouvee
 * @return true si la ville a ete trouvee, false sinon
 * @note Fonction 8
 */
bool chercherVille(int numeroVille, Chaine ville) {
    //  a completer
}

/**
 * @brief Verifie qu'une ville se trouve dans la liste des villes
 * @param ville : la ville qui doit etre testee
 * @return true si la ville existe, false sinon
 * @note Fonction 9
 */
bool villeExiste(Chaine ville) {
    //  a completer
}

/**
 * @brief Retourne la distance entre 2 villes
 * @param ville1 : premiere ville
 * @param ville2 : deuxieme ville
 * @return la distance entre les 2 villes
 * @endcode EXIT_FAILURE si l'une des 2 villes n'existe pas
 * @note Fonction 10
 */
double distanceVilles(Chaine ville1, Chaine ville2) {
    //  a completer
}

//  Fonctions 11 a 14 : manipulation des etapes
//  -------------------------------------------

/**
 * @brief Affiche une etape (passee en parametre).
 * @param etape : l'etape a afficher
 * @example
 * Ville de depart : Montreal\n
 * Ville d'arrivee : Gatineau\n
 * Distance : 123.4 Km\n
 * Locomotion : par route\n
 * Nombre de pauses : 1\n
 * Duree : 1h23'\n\n
 * ou encore\n\n
 * Ville de depart : Montreal\n
 * Ville d'arrivee : Halifax\n
 * Distance : 1234.5 Km\n
 * Locomotion : par avion\n
 * Temps d'attente : 2h30'\n
 * Duree : 4h56'\n
 * @note Fonction 11
 */
void afficherEtape(Etape etape) {
    //  a completer
}

/**
 * @brief Initialise une etape selon la ville de depart et la ville d'arrivee
 * @param depart : la ville de depart
 * @param arrivee : la ville d'arrivee
 * @param etape : l'etape qui doit etre initialisee
 * @return false si l'une des villes n'est pas dans le fichier des distances, true sinon
 * @note Fonction 12
 */
bool preparerEtape(Chaine depart, Chaine arrivee, Etape etape) {
    //  a completer
}

/**
 * @brief Ajoute une etape dans un fichier d'etapes
 * @param fichier : le fichier d'etapes a mettre a jour
 * @param etape : l'etape a ajouter au fichier
 * @return true si tout s'est bien passe, false sinon
 * @note Fonction 13
 * @todo Gerer les erreur possibles !
 */
bool fichierAjouterEtape(Fichier fichier, Etape etape) {
    //  a completer
}

/**
 * @brief Cree un fichier d'etapes en partant d'un fichier qui decrit la liste des villes a parcourir
 * @param nomFichierVoyage : le nom du fichier qui contient la liste des villes du voyage
 * @param nomFichierEtapes : le nom du fichier d'etapes a creer
 * @return true si tout s'est bien passe, false sinon
 * @note Fonction 14
 * @todo Gerer les erreur possibles !
 */
bool creerFichierEtapes(Chaine nomFichierVoyage, Chaine nomFichierEtapes) {
    //  a completer
}

//  Fonctions 15 et 16 : creation et affichage des statistiques
//  -----------------------------------------------------------

/**
 * @brief Affiche les statistique de voyage passees en parametre
 * @param stats : les statistiques a afficher
 * @example Nombre d'etapes par route : 3\n
 * Nombre d'etapes par air : 1\n
 * Nombre de pauses : 2\n
 * Temps d'attente : 2h30'\n
 * @note Fonction 15
 */
void afficherStatistiques(Statistiques stats) {
    //  a completer
}

/**
 * @brief Calcule les statistiques pour un ensemble d'etapes
 * @param nomFichierEtapes : le fichier contenant les etapes
 * @param stats : la variable de statistiques a initialiser
 * @return
 * @note Fonction 16
 */
bool creerStatistiques(Chaine nomFichierEtapes, Statistiques stats) {
    //  a completer
}

// -------------------------------------------------------------------------------------------------------------------
//  Fonction de tests

void test_afficherDuree() {
    double duree = 0;

    printf("Quelle est la duree en decimale: ");
    scanf(" %lf", &duree);

    afficherDuree(duree);
}

void test_villesEgales() {
   
    Chaine ville1 = "Montreal";
    Chaine ville2 = "Mirabel";
    
    printf("Veuillez entrer les deux villes a comparer: ");
    scanf(" %s %s", ville1, ville2);

    villesEgales(ville1, ville2);
}

void test_fichierLireEntier() {

    Fichier fichier;
    int resultat;

    fichier = fichierOuvrirLecture(FICHIER_DES_DISTANCES);

    Chaine c;
    fichierLireChaine(fichier, c);
    printf("%s\n", c);

    for (int i = 0; i < 4; i++) {
        resultat = fichierLireEntier(fichier);
        printf("%lf\n", resultat);
    }
}


void test_fichierLireReel() {

	Fichier fichier;
	double resultat;

	fichier = fichierOuvrirLecture(FICHIER_DES_DISTANCES);

	Chaine c;
	fichierLireChaine(fichier, c);
	printf("%s\n", c);

	for (int i = 0; i < 4; i++) {
		resultat = fichierLireReel(fichier);
		printf("%lf\n", resultat);
	}
}

void test_fichierAvancerChamps() {

    Fichier fichier;
    double resultat;

    fichier = fichierOuvrirLecture(FICHIER_DES_DISTANCES);

    fichierAvancerChamps(fichier, 7);

    resultat = fichierLireReel(fichier);
    printf("%lf\n", resultat);
}

void test_fichierAvancerLignes() {

    Fichier fichier;

    fichier = fichierOuvrirLecture(FICHIER_DES_DISTANCES);

    if (fichierAvancerLignes(fichier, 3)) {
        printf("Echec de l'avancement des lignes, car la fin du fichier a ete atteinte\n");
    }
    else {
        printf("Succes de l'avancement des lignes\n");
    }
}

void test_chercherNumeroVille() {
    //  a completer
}

void test_fichierChercherVille() {
    //  a completer
}

void test_villeExiste() {
    //  a completer
}

void test_distanceVilles() {
    //  a completer
}

void test_afficherEtape() {
    //  a completer
}

void test_preparerEtape() {
    //  a completer
}

void test_fichierAjouterEtape() {
    //  a completer
}

void test_creerFichierEtapes() {
    //  a completer
}

void test_afficherStatistiques() {
    //  a completer
}

void test_creerStatistiques() {
    //  a completer
}

// -------------------------------------------------------------------------------------------------------------------

int main() {
    srand(time(NULL));

    test_afficherDuree();
    printf("------------------------------------------------------------------------------------------------------\n");
    test_villesEgales();
    printf("------------------------------------------------------------------------------------------------------\n");
    test_fichierLireEntier();
    printf("------------------------------------------------------------------------------------------------------\n");
    test_fichierLireReel();
    printf("------------------------------------------------------------------------------------------------------\n");
    test_fichierAvancerChamps();
    printf("------------------------------------------------------------------------------------------------------\n");
    test_fichierAvancerLignes();
    printf("------------------------------------------------------------------------------------------------------\n");
    test_chercherNumeroVille();
    printf("------------------------------------------------------------------------------------------------------\n");
    test_fichierChercherVille();
    printf("------------------------------------------------------------------------------------------------------\n");
    test_villeExiste();
    printf("------------------------------------------------------------------------------------------------------\n");
    test_distanceVilles();
    printf("------------------------------------------------------------------------------------------------------\n");
    test_afficherEtape();
    printf("------------------------------------------------------------------------------------------------------\n");
    test_preparerEtape();
    printf("------------------------------------------------------------------------------------------------------\n");
    test_fichierAjouterEtape();
    printf("------------------------------------------------------------------------------------------------------\n");
    test_creerFichierEtapes();
    printf("------------------------------------------------------------------------------------------------------\n");
    test_afficherStatistiques();
    printf("------------------------------------------------------------------------------------------------------\n");
    test_creerStatistiques();

    return 0;
}
