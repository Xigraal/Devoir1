#pragma once

//
// Created by stephane on 04/05/24.
//

#ifndef CODE_UTILITAIRE_H
#define CODE_UTILITAIRE_H

#include <stdio.h>
#include <stdbool.h>

typedef char Chaine[50];
typedef FILE *Fichier;

//  fonctions generales sur les fichiers
//  ------------------------------------
Fichier fichierOuvrirLecture(Chaine nomFichier);

Fichier fichierOuvrirEcriture(Chaine nomFichier);

void fichierFermer(Fichier fichier);

bool fichierLireChaine(Fichier fichier, Chaine chaine);

void fichierEcrireChaine(Fichier fichier, Chaine chaine);

bool fichierLigneSuivante(Fichier fichier);

bool finDeFichier(Fichier f);

//  fonctions generales sur les chaines de caracteres
//  -------------------------------------------------
bool chainesEgales(Chaine ville1, Chaine ville2);

void chainesCopier(Chaine source, Chaine destination);

bool entierVersChaine(int n, Chaine chaine);

bool reelVersChaine(double x, Chaine c);

#endif //CODE_UTILITAIRE_H
