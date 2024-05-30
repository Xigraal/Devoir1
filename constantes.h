#pragma once

#define FICHIER_DES_DISTANCES "../distances.csv"

#define DUREE_PAUSE 0.25            //  duree de la pause lors d'un deplacement par voiture
#define DISTANCE_MAX_ROUTE 600      //  pas plus que 600 Km par route, sinon, par avion
#define VITESSE_PAR_ROUTE 90        //  vitesse moyenne de deplacement par la route
#define VITESSE_PAR_AIR 850         //  vitesse moyenne de deplacement par avion

#define PAUSE_VOITURE 100           //  une pause tous les 100 Km
#define LIMITE_ATTENTE_AVION 1000   //  avant 1000 Km, 1.5 h d'attente, apres 2.5 h d'attente
#define ATTENTE_AVION_MIN 1.5       //  attente minimale (1h30')
#define ATTENTE_AVION_MAX 2.5       //  attente maximale (2h30')
#define MINUTES_PAR_HEURE 60        

//  codes d'erreurs
#define VILLE_NON_TROUVEE (-1)
