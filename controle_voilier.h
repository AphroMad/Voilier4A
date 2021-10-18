#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"

/** Fonction d'initialisation du moteur */
void init_moteur(void);

void start_moteur(void);
void stop_moteur(void);


/** Fonction qui oriente le moteur 
	* @param orientation Booleen qui oriente à gauche si vrai, à droite si faux
	* @param vitesse valeur entre 0 et 100% de la vitesse maximale du voilier
	*/
void set_motor(int orientation, int vitesse);