#ifndef TIMER_H
#define TIMER_H

#include <stm32f10x.h>
#include <utils.h>

enum Timer_Slave_Mode {
	TIMER_SLAVE_MODE_DISABLED = 0, ///< Comptage à la fréquence de l'horloge
	TIMER_SLAVE_MODE_ENCODER_1 = 1, ///< Incrémentation/Décrémentation à chaque front de TI2FP1 selon le niveau de TI1FP2
	TIMER_SLAVE_MODE_ENCODER_2 = 2, ///< Incrémentation/Décrémentation à chaque front de TI1FP2 selon le niveau de TI2FP1
	TIMER_SLAVE_MODE_ENCODER_3 = 3, ///< Incrémentation/Décrémentation à chaque front de TI1FP2 selon le niveau d'une autre entrée
	TIMER_SLAVE_MODE_RESET = 4,
	TIMER_SLAVE_MODE_GATED = 5,
	TIMER_SLAVE_MODE_TRIGGER = 6,
	TIMER_SLAVE_MODE_EXTERNAL = 7,
};

/*!
 * Structure présentant les différents paramètres pour un timer, utilisé en tant que premier argument des fonctions Timer_*
 */
struct Timer {
	TIM_TypeDef *timer; ///< Addresse du Timer assocé
	uint16_t psc; ///< Valeur du PSC du timer, diviseur de la fréquence de base (72MHz)
	uint16_t arr; ///< Valeur de l'ARR du timer, valeur max du compteur
	enum Timer_Slave_Mode slave_mode; ///< Mode de comptage
};

/*!
 * Initialisation d'un timer
 */
void Timer_Init(struct Timer *timer);

void Timer_Start(struct Timer *timer);

#endif // TIMER_H
