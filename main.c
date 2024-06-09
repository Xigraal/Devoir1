//
// Created by stephane on 04/05/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "utilitaire.h"
#include "structures.h"
#include "constantes.h"

// commentaires faites par chatgpt

// derclaration des fonctions
void calcul_duree(double duree, int* part_entiere, int* minutes);

//  Fonctions 1 et 2 : affichage d'une duree et test d'egalite de 2 villes
//  ----------------------------------------------------------------------

/**
 * @brief Affiche une duree donnees en decimales, en heures et minutes
 * @param duree : le temps en heures a afficher
 * @example affichera 3h15' pour une duree de 3.25. Ou encore 1h20' pour une duree de 1.33
 * @note Fonction 1
 */
void afficherDuree(double duree) {
    int part_entiere;
    int minutes;

    // Calculer la durée en heures et minutes
    calcul_duree(duree, &part_entiere, &minutes);

    // Afficher la durée au format approprié
    if (minutes < 10) {
        printf(" %dh0%d'\n", part_entiere, minutes);
    }
    else {
        printf(" %dh%d'\n", part_entiere, minutes);
    }
}

/**
 * @brief Calcul une duree donnees en decimales, en heures et minutes
 * @param duree : le temps en heures a calculer
 * @param minutes : les minutes passes par references
 * @param part_entiere : L'heure passee par references
 * @example Calculera 3h15' pour une duree de 3.25. Ou encore 1h20' pour une duree de 1.33
 * @note Fonction 1.1
 */
void calcul_duree(double duree, int* part_entiere, int* minutes) {
    double part_decimale;

    *part_entiere = duree;  // Extraire la partie entière
    part_decimale = duree - *part_entiere;  // Calculer la partie décimale

    // Convertir la partie décimale en minutes
    *minutes = (part_decimale * MINUTES_DANS_UNE_HEURE) + FACTEUR_DE_CORRECTION; 
}

/**
 * @brief Teste si 2 villes sont egales
 * @param ville1 : la premiere ville
 * @param ville2 : la seconde ville
 * @return true si les 2 villes sont les memes, false sinon
 * @note Fonction 2
 */
bool villesEgales(Chaine ville1, Chaine ville2) {
    // Comparer les deux chaînes de caractères pour vérifier l'égalité des villes
    return chainesEgales(ville1, ville2);
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

    // Vérifier si la fin du fichier a été atteinte
    if (finDeFichier(fichier)) {
        fprintf(stderr, "Erreur: la fin de fichier a été atteinte\n");
        exit(EXIT_FAILURE);
    }

    // Lire la chaîne de caractères suivante
    bool valide = fichierLireChaine(fichier, chaine);

    // Convertir la chaîne en entier et la retourner
    if (valide) {
        return atoi(chaine);
    }
    else {
        fprintf(stderr, "Erreur de lecture du fichier\n");
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

    // Lire la chaîne de caractères suivante
    bool valide = fichierLireChaine(fichier, chaine);

    // Convertir la chaîne en réel et la retourner
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

    // Avancer de n champs dans le fichier
    while (i < n && fichierLireChaine(fichier, chaine)) {
        i++;
    }

    // Vérifier si le nombre de champs avancé est égal à n
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
    // Avancer de n lignes dans le fichier
    for (int i = 1; i < n; i++) {
        if (!fichierLigneSuivante(fichier)) {
            return false;
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
    Chaine c;

    fichier = fichierOuvrirLecture(FICHIER_DES_DISTANCES);

    // Parcourir le fichier pour trouver la ville
    while (!finDeFichier(fichier)) {
        numero_de_ligne += 1;

        if (!fichierLireChaine(fichier, c)) {
            fprintf(stderr, "Erreur de lecture du fichier\n");
            fichierFermer(fichier);
            exit(EXIT_FAILURE);
        }

        // Vérifier si la ville est trouvée dans la chaîne actuelle
        if (strstr(c, ville) != NULL) {
            fichierFermer(fichier);
            return numero_de_ligne;
        }

        // Passer à la ligne suivante du fichier
        if (!fichierLigneSuivante(fichier)) {
            break;
        }
    }

    fichierFermer(fichier);
    return -1;
}

/**
 * @brief Cherche une ville dans la liste des villes a partir de son numero
 * @param numeroVille : le numero de la ville dans le fichier des villes
 * @param ville : la ville trouvee
 * @return true si la ville a ete trouvee, false sinon
 * @note Fonction 8
 */
bool chercherVille(int numeroVille, Chaine ville) {
    Fichier fichier;

    // Ouvrir le fichier de distances en lecture
    fichier = fichierOuvrirLecture(FICHIER_DES_DISTANCES);

    // Avancer jusqu'à la ligne correspondant au numéro de ville
    if (fichierAvancerLignes(fichier, numeroVille)) {
        // Lire la chaîne de caractères de la ville trouvée
        fichierLireChaine(fichier, ville);

        // Fermer le fichier
        fichierFermer(fichier);

        return true;
    }
    else {
        fichierFermer(fichier);
        return false;
    }
}

/**
 * @brief Verifie qu'une ville se trouve dans la liste des villes
 * @param ville : la ville qui doit etre testee
 * @return true si la ville existe, false sinon
 * @note Fonction 9
 */
bool villeExiste(Chaine ville) {
    // Chercher le numéro de la ville, retourne vrai si trouvé
    return chercherNumeroVille(ville) != VILLE_NON_TROUVEE;
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
    int numeroVille1;
    int numeroVille2;
    double distance;

    Fichier fichier = fichierOuvrirLecture(FICHIER_DES_DISTANCES);

    // Vérifier si la première ville existe
    numeroVille1 = chercherNumeroVille(ville1);
    if (!villeExiste(ville1)) {
        fprintf(stderr, "La Ville de %s n'a pas ete trouvee\n", ville1);
        fichierFermer(fichier);
        exit(EXIT_FAILURE);
    }

    // Vérifier si la seconde ville existe
    numeroVille2 = chercherNumeroVille(ville2);
    if (!villeExiste(ville2)) {
        fprintf(stderr, "Ville '%s' non trouvee\n", ville2);
        fichierFermer(fichier);
        exit(EXIT_FAILURE);
    }

    // Avancer jusqu'à la ligne correspondant à la première ville
    if (!fichierAvancerLignes(fichier, numeroVille1)) {
        fprintf(stderr, "Erreur de deplacement a la ligne %d\n", numeroVille1);
        fichierFermer(fichier);
        exit(EXIT_FAILURE);
    }

    // Avancer jusqu'à la colonne correspondant à la seconde ville
    if (!fichierAvancerChamps(fichier, numeroVille2)) {
        fprintf(stderr, "Erreur de deplacement a la colonne %d\n", numeroVille2);
        fichierFermer(fichier);
        exit(EXIT_FAILURE);
    }

    // Lire la distance entre les deux villes
    if (!fichierLireReel(fichier)) {
        fprintf(stderr, "Erreur de lecture de la distance\n");
        fichierFermer(fichier);
        exit(EXIT_FAILURE);
    }

    distance = fichierLireReel(fichier);

    fichierFermer(fichier);

    return distance;
}

//  Fonctions 11 a 14 : manipulation des etapes
//  ------------------------------------------

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
    Chaine ville1;
    Chaine ville2;

    // Chercher les noms des villes de départ et d'arrivée
    chercherVille((int)etape[ETAPE_VILLE_DEPART], ville1);
    chercherVille((int)etape[ETAPE_VILLE_ARRIVEE], ville2);

    // Afficher les informations de l'étape
    printf("Ville de depart : %s\n", ville1);
    printf("Ville d'arrivee : %s\n", ville2);

    // Afficher les détails de l'étape selon le type de locomotion
    if (etape[ETAPE_DISTANCE] <= DISTANCE_MAX_ROUTE) {
        printf("Distance : %.2lf Km\n", etape[ETAPE_DISTANCE]);
        printf("Locomotion : par route\n");
        printf("Nombre de pauses : %d\n", (int)etape[ETAPE_PAUSES]);
        printf("Duree : ");
        afficherDuree(etape[ETAPE_DUREE]);
    }
    else {
        printf("Distance : %.2lf Km\n", etape[ETAPE_DISTANCE]);
        printf("Locomotion : par avion\n");
        printf("Temps d'attente :");
        afficherDuree(etape[ETAPE_ATTENTE]);
        printf("Duree : ");
        afficherDuree(etape[ETAPE_DUREE]);
    }
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
    // Vérifier l'existence des villes
    if (villeExiste(depart) < 0 && villeExiste(arrivee) < 0) {
        return false;
    }

    // Initialiser les informations de l'étape
    etape[ETAPE_VILLE_DEPART] = chercherNumeroVille(depart);
    etape[ETAPE_VILLE_ARRIVEE] = chercherNumeroVille(arrivee);
    etape[ETAPE_DISTANCE] = distanceVilles(depart, arrivee);
    etape[ETAPE_PAUSES] = etape[ETAPE_DISTANCE] / PAUSE_VOITURE;

    // Définir le temps d'attente selon la distance
    if (etape[ETAPE_DISTANCE] < LIMITE_ATTENTE_AVION) {
        etape[ETAPE_ATTENTE] = ATTENTE_AVION_MIN;
    }
    else {
        etape[ETAPE_ATTENTE] = ATTENTE_AVION_MAX;
    }

    // Calculer la durée de l'étape selon le mode de locomotion
    if (etape[ETAPE_DISTANCE] <= DISTANCE_MAX_ROUTE) {
        etape[ETAPE_LOCOMOTION] = LOCOMOTION_PAR_ROUTE;
        etape[ETAPE_DUREE] = (etape[ETAPE_DISTANCE] / VITESSE_PAR_ROUTE) + etape[ETAPE_PAUSES] * DUREE_PAUSE;
    }
    else {
        etape[ETAPE_LOCOMOTION] = LOCOMOTION_PAR_AIR;
        etape[ETAPE_DUREE] = (etape[ETAPE_DISTANCE] / VITESSE_PAR_AIR) + etape[ETAPE_ATTENTE];
    }

    return true;
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
    Chaine ville1;
    Chaine ville2;
    int part_entiere;
    int minutes;

    // Chercher les noms des villes de départ et d'arrivée
    chercherVille((int)etape[ETAPE_VILLE_DEPART], ville1);
    chercherVille((int)etape[ETAPE_VILLE_ARRIVEE], ville2);

    // Ajouter les informations de l'étape dans le fichier
    if (fprintf(fichier, "Ville de depart : %s\n", ville1) < 0) return false;
    if (fprintf(fichier, "Ville d'arrivee : %s\n", ville2) < 0) return false;

    // Calculer la distance et les pauses
    etape[ETAPE_DISTANCE] = distanceVilles(ville1, ville2);
    etape[ETAPE_PAUSES] = etape[ETAPE_DISTANCE] / PAUSE_VOITURE;

    // Définir le temps d'attente selon la distance
    if (etape[ETAPE_DISTANCE] < LIMITE_ATTENTE_AVION) {
        etape[ETAPE_ATTENTE] = ATTENTE_AVION_MIN;
    }
    else {
        etape[ETAPE_ATTENTE] = ATTENTE_AVION_MAX;
    }

    // Ajouter les détails de l'étape selon le mode de locomotion
    if (etape[ETAPE_DISTANCE] <= DISTANCE_MAX_ROUTE) {
        // Si distance <= DISTANCE_MAX_ROUTE, locomotion par route
        etape[ETAPE_LOCOMOTION] = LOCOMOTION_PAR_ROUTE;
        etape[ETAPE_DUREE] = (etape[ETAPE_DISTANCE] / VITESSE_PAR_ROUTE) + etape[ETAPE_PAUSES] * DUREE_PAUSE;

        
        calcul_duree(etape[ETAPE_DUREE], &part_entiere, &minutes);

        // Écriture des informations de l'étape dans le fichier
        if (fprintf(fichier, "Distance : %.2lf Km\n", etape[ETAPE_DISTANCE]) < 0) return false;
        if (fprintf(fichier, "Locomotion : par route\n") < 0) return false;
        if (fprintf(fichier, "Nombre de pauses : %d\n", etape[ETAPE_PAUSES]) < 0) return false;
        if (fprintf(fichier, "Duree : %dh%d'\n", part_entiere, minutes) < 0) return false;
    }
    else {
        // Sinon, locomotion par avion
        etape[ETAPE_LOCOMOTION] = LOCOMOTION_PAR_AIR;
        etape[ETAPE_DUREE] = (etape[ETAPE_DISTANCE] / VITESSE_PAR_AIR) + etape[ETAPE_ATTENTE];

        
        calcul_duree(etape[ETAPE_DUREE], &part_entiere, &minutes);

        // Écriture des informations de l'étape dans le fichier
        if (fprintf(fichier, "Distance : %.2lf Km\n", etape[ETAPE_DISTANCE]) < 0) return false;
        if (fprintf(fichier, "Locomotion : par avion\n") < 0) return false;
        if (fprintf(fichier, "Temps d'attente : %.2lf\n", etape[ETAPE_ATTENTE]) < 0) return false;
        if (fprintf(fichier, "Duree : %dh%d'\n", part_entiere, minutes) < 0) return false;
    }

    // Vérifier si le fichier est null
    if (fichier == NULL) {
        fprintf(stderr, "Erreur : fichier manquant\n");
        return false;
    }

    return true;
}

/**
 * @brief Cree un fichier d'etapes en partant d'un fichier qui decrit la liste des villes a parcourir
 * @param nomFichierVoyage : le nom du fichier qui contient la liste des villes du voyage
 * @param nomFichierEtapes : le nom du fichier d'etapes a creer
 * @return true si tout s'est bien passe, false sinon
 * @note Fonction 14
 * @todo Gerer les erreur possibles !
 */
bool creerFichierEtapes(Chaine nom_fichier_voyage, Chaine nom_fichier_etapes) {
    // Ouvrir le fichier des villes en lecture
    Fichier fichier_voyage = fichierOuvrirLecture(nom_fichier_voyage);
    if (fichier_voyage == NULL) {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier des villes %s\n", nom_fichier_voyage);
        return false;
    }

    // Ouvrir le fichier des étapes en écriture
    Fichier fichier_etapes = fichierOuvrirEcriture(nom_fichier_etapes);
    if (fichier_etapes == NULL) {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier des etapes %s\n", nom_fichier_etapes);
        fichierFermer(fichier_voyage);
        return false;
    }

    Etape etape;
    Chaine depart, arrivee;

    // Lire les villes de depart et arrivee
    fichierLireChaine(fichier_voyage, depart);
    fichierLireChaine(fichier_voyage, arrivee);

    // Lire les villes du fichier et préparer les étapes
    while (!finDeFichier(fichier_voyage)) {
        if (!preparerEtape(depart, arrivee, etape)) {
            fprintf(stderr, "Erreur : preparation de l'etape entre %s et %s\n", depart, arrivee);
            fichierFermer(fichier_voyage);
            fichierFermer(fichier_etapes);
            return false;
        }

        if (!fichierAjouterEtape(fichier_etapes, etape)) {
            fprintf(stderr, "Erreur : ajout de l'etape entre %s et %s\n", depart, arrivee);
            fichierFermer(fichier_voyage);
            fichierFermer(fichier_etapes);
            return false;
        }

        // Copier la ville d'arrivée comme nouvelle ville de départ
        chainesCopier(arrivee, depart);

        // Lire la prochaine ville
        if (!fichierLireChaine(fichier_voyage, arrivee)) {
            fprintf(stderr, "Erreur : impossible de lire la prochaine ville dans %s\n", nom_fichier_voyage);
            fichierFermer(fichier_voyage);
            fichierFermer(fichier_etapes);
            return false;
        }
    }

    // Préparer et ajouter la dernière étape
    if (!preparerEtape(depart, arrivee, etape)) {
        fprintf(stderr, "Erreur : preparation de l'etape entre %s et %s\n", depart, arrivee);
        fichierFermer(fichier_voyage);
        fichierFermer(fichier_etapes);
        return false;
    }

    
    if (!fichierAjouterEtape(fichier_etapes, etape)) {
        fprintf(stderr, "Erreur : ajout de l'etape entre %s et %s\n", depart, arrivee);
        fichierFermer(fichier_voyage);
        fichierFermer(fichier_etapes);
        return false;
    }

    // Fermer les fichiers
    fichierFermer(fichier_voyage);
    fichierFermer(fichier_etapes);

    return true;
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
    printf("Nombre d'etapes par route : %.0f\n", stats[STATS_NB_ETAPES_PAR_ROUTE]);
    printf("Nombre d'etapes par air : %.0f\n", stats[STATS_NB_ETAPES_PAR_AIR]);
    printf("Nombre de pauses : %.0f\n", stats[STATS_NB_PAUSES]);
    printf("Temps d'attente : ");
    afficherDuree(stats[STATS_TEMPS_ATTENTE]);
}

/**
 * @brief Calcule les statistiques pour un ensemble d'etapes
 * @param nomFichierEtapes : le fichier contenant les etapes
 * @param stats : la variable de statistiques a initialiser
 * @return
 * @note Fonction 16
 */
bool creerStatistiques(Chaine nomFichierEtapes, Statistiques stats) {
    // Ouvrir le fichier des étapes en lecture
    Fichier fichier_etapes = fichierOuvrirLecture(nomFichierEtapes);

    if (fichier_etapes == NULL) {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier des etapes %s\n", nomFichierEtapes);
        return false;
    }

    Chaine chaine;

    // Initialiser les statistiques
    stats[STATS_NB_ETAPES_PAR_ROUTE] = 0.0;
    stats[STATS_NB_ETAPES_PAR_AIR] = 0.0;
    stats[STATS_NB_PAUSES] = 0.0;
    stats[STATS_TEMPS_ATTENTE] = 0.0;

    // Lire les étapes du fichier et calculer les statistiques
    while (fichierLireChaine(fichier_etapes, chaine)) {
        if (chainesEgales("route", chaine)) {
            // Si l'étape est par route, incrémenter le compteur
            stats[STATS_NB_ETAPES_PAR_ROUTE]++;

            // Avancer d'une ligne et quatre champs pour lire le nombre de pauses
            if (fichierAvancerLignes(fichier_etapes, 1) && fichierAvancerChamps(fichier_etapes, 4)) {
                fichierLireChaine(fichier_etapes, chaine);
                stats[STATS_NB_PAUSES] += atof(chaine);
            }
        }
        else if (chainesEgales("avion", chaine)) {
            // Si l'étape est par avion, incrémenter le compteur
            stats[STATS_NB_ETAPES_PAR_AIR]++;

            // Lire et ignorer le temps de vol
            fichierLireReel(fichier_etapes);

            // Avancer d'une ligne et deux champs pour lire le temps d'attente
            if (fichierAvancerLignes(fichier_etapes, 1) && fichierAvancerChamps(fichier_etapes, 2)) {
                fichierLireChaine(fichier_etapes, chaine);
                stats[STATS_TEMPS_ATTENTE] += atof(chaine);
            }
        }
    }

    // Fermer le fichier des étapes
    fichierFermer(fichier_etapes);
    return true;
}

// -------------------------------------------------------------------------------------------------------------------
//  Fonction de tests

void test_afficherDuree() {
    double duree = 0.0;

    duree = 3.25;
    afficherDuree(duree);

    duree = 1.1;
    afficherDuree(duree);

    duree = 1.33;
    afficherDuree(duree);
}

void test_villesEgales() {
    Chaine ville1 = "Montreal";
    Chaine ville2 = "Toronto";

    villesEgales(ville1, ville2);

    if (villesEgales(ville1, ville2) == true) {
        printf(" Les deux villes sont pareils\n");
    }
    else {
        printf(" Les deux villes sont differentes\n");
    }
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
        printf("%d\n", resultat);
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
        printf("%.2lf\n", resultat);
    }
}

void test_fichierAvancerChamps() {
    Fichier fichier;
    double resultat;

    fichier = fichierOuvrirLecture(FICHIER_DES_DISTANCES);

    fichierAvancerChamps(fichier, 2);

    resultat = fichierLireReel(fichier);
    printf("La valeur dans ce champs est: %.2lf\n", resultat);
}

void test_fichierAvancerLignes() {
    Fichier fichier;

    fichier = fichierOuvrirLecture(FICHIER_DES_DISTANCES);

    if (!fichierAvancerLignes(fichier, 3)) {
        printf("Echec de l'avancement des lignes, car la fin du fichier a ete atteinte\n");
    }
    else {
        printf("Succes de l'avancement des lignes\n");
    }
}

void test_chercherNumeroVille() {
    Chaine ville = "MedicineHat";
    int resultat;

    resultat = chercherNumeroVille(ville);
    printf("Le numero de la ville est: %d\n", resultat);
}

void test_fichierChercherVille() {
    int numero_ville = 45;
    Chaine ville;

    chercherVille(numero_ville, ville);
    printf("La ville rechercher est: %s\n", ville);
}

void test_villeExiste() {
    Chaine ville = "Montreal";

    if (!villeExiste(ville)) {
        printf("La ville n'existe pas.\n");
    }
    else {
        printf("La ville existe.\n");
    }
}

void test_distanceVilles() {
    double distance;
    Chaine ville1 = "Montreal";
    Chaine ville2 = "Calgary";

    distance = distanceVilles(ville1, ville2);
    printf("La distance entre les deux villes est: %.2lf\n", distance);
}

void test_afficherEtape() {
    Etape etape = { 0 };

    etape[ETAPE_VILLE_DEPART] = 1;
    etape[ETAPE_VILLE_ARRIVEE] = 20;

    Chaine depart;
    Chaine arrivee;

    chercherVille((int)etape[ETAPE_VILLE_DEPART], depart);
    chercherVille((int)etape[ETAPE_VILLE_ARRIVEE], arrivee);

    if (!preparerEtape(depart, arrivee, etape)) {
        printf("L'une des villes n'est pas dans le fichier des distances.\n");
    }
    else {
        printf("Exemple 1 d'etape:\n");
        afficherEtape(etape);
    }
}

void test_preparerEtape() {
    Chaine depart = "Montreal";
    Chaine arrivee = "Quebec";
    Etape etape;

    if (!preparerEtape(depart, arrivee, etape)) {
        printf("L'une des villes n'est pas dans le fichier des distances.\n");
    }
    else {
        afficherEtape(etape);
    }
}

void test_fichierAjouterEtape() {
    Etape etape = { 1, 20 };

    FILE* fichier = fichierOuvrirEcriture(FICHIER_ETAPE);
    if (!fichier) {
        fprintf(stderr, "Erreur: impossible d'ouvrir le fichier en ecriture\n");
        return;
    }

    if (!fichierAjouterEtape(fichier, etape)) {
        fprintf(stderr, "Erreur: impossible d'ajouter l'etape\n");
        fichierFermer(fichier);
        return;
    }

    fichierFermer(fichier);

    printf("Test reussi: l'etape a ete ajoutee avec succes.\n");
}

void test_creerFichierEtapes() {
    Chaine nomFichierVoyage = FICHIER_VOYAGE;
    Chaine nomFichierEtapes = FICHIER_ETAPE;

    if (creerFichierEtapes(FICHIER_VOYAGE, FICHIER_ETAPE)) {
        printf("Succes du test : le fichier d'etapes a ete cree avec succes.\n");
    }
    else {
        printf("Echec du test : une erreur est survenue lors de la creation du fichier d'etapes.\n");
    }
}

void test_afficherStatistiques() {
    Statistiques stats = { 1, 1, 2, 2.5 };
    printf("Les statistiques du test sont:\n");
    afficherStatistiques(stats);
}

void test_creerStatistiques() {
    Statistiques stats;

    creerStatistiques(FICHIER_ETAPE, stats);

    printf("Les statistiques des etapes du fichier sont:\n");
    afficherStatistiques(stats);
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
