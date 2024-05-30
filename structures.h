#pragma once

//
// Created by stephane on 04/05/24.
//

#ifndef CODE_STRUCTURES_H
#define CODE_STRUCTURES_H

//  Le type pour coder une etape (un tableau de 6 nombres de type double).
//  Chaque information de l'etape est placee dans une case du tableau.
//  C'est l'indice de la case qui indique la signification de l'information stockee.
typedef double Etape[6];

//  Constantes qui precisent la signification de l'information selon l'indice de la case dans le tableau precedent.
//  Ainsi, a l'indice 0 (= ETAPE_VILLE_DEPART), on aura le numero de la ville de depart.
//  De meme, a l'indice 3 (= ETAPE_LOCOMOTION), on aura le code du moyen de locomotion (voir *)
//  L'indice 4 apparait 2 fois, car on y place, soit un nombre de pauses dans le cas d'une etape par route, soit
//  un temps d'attente dans le cas d'une etape par air.
#define ETAPE_VILLE_DEPART  0   //  indice du numero de la ville de depart
#define ETAPE_VILLE_ARRIVEE 1   //  indice du numero de la ville d'arrivee
#define ETAPE_DISTANCE      2   //  indice de la distance de l'etape
#define ETAPE_LOCOMOTION    3   //  indice du moyen de locomotion (LOCOMOTION_PAR_ROUTE ou LOCOMOTION_PAR_AIR)
#define ETAPE_PAUSES        4   //  indice du nombre de pauses pour une etape par route
#define ETAPE_ATTENTE       4   //  indice du temps d'attente pour une etape par air
#define ETAPE_DUREE         5   //  indice de la duree de l'etape

//  Definition des constantes pour coder le moyen de locomotion (par route ou par air).
//  (*) Ce sont ces valeurs qui seront placees dans la case d'indice 3 du tableau d'une etape.
#define LOCOMOTION_PAR_ROUTE    0   //  codage pour une locomotion par route
#define LOCOMOTION_PAR_AIR      1   //  codage pour une locomotion par air

//  Le type pour coder les statistiques (un tableau de 4 nombre de type double)
//  On utilise ici le meme principe que pour le tableau d'un etape.
typedef double Statistiques[4];
#define STATS_NB_ETAPES_PAR_ROUTE   0       //  indice du nombre d'etapes par route
#define STATS_NB_ETAPES_PAR_AIR     1       //  indice du nombre d'etapes par avion
#define STATS_NB_PAUSES             2       //  indice du nombre de pauses pour les etapes par voiture
#define STATS_TEMPS_ATTENTE         3       //  indice du temps total d'attente pour les etapes par avion

#endif //CODE_STRUCTURES_H
