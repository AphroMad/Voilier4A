#ifndef TIMER_H
#define TIMER_H

#include <stm32f10x.h>
#include <utils.h>

enum Timer_Slave_Mode {
	TIMER_SLAVE_MODE_DISABLED = 0, ///< Comptage � la fr�quence de l'horloge
	TIMER_SLAVE_MODE_ENCODER_1 = 1, ///< Incr�mentation/D�cr�mentation � chaque front de TI2FP1 selon le niveau de TI1FP2
	TIMER_SLAVE_MODE_ENCODER_2 = 2, ///< Incr�mentation/D�cr�mentation � chaque front de TI1FP2 selon le niveau de TI2FP1
	TIMER_SLAVE_MODE_ENCODER_3 = 3, ///< Incr�mentation/D�cr�mentation � chaque front de TI1FP2 selon le niveau d'une autre entr�e
	TIMER_SLAVE_MODE_RESET = 4,
	TIMER_SLAVE_MODE_GATED = 5,
	TIMER_SLAVE_MODE_TRIGGER = 6,
	TIMER_SLAVE_MODE_EXTERNAL = 7,
};

/*!
 * Structure pr�sentant les diff�rents param�tres pour un timer, utilis� en tant que premier argument des fonctions Timer_*
 */
struct Timer {
	TIM_TypeDef *timer; ///< Addresse du Timer assoc�
	uint16_t psc; ///< Valeur du PSC du timer, diviseur de la fr�quence de base (72MHz)
	uint16_t arr; ///< Valeur de l'ARR du timer, valeur max du compteur
	enum Timer_Slave_Mode slave_mode; ///< Mode de comptage
};

/*!
 * Initialisation d'un timer
 */
void Timer_Init(struct Timer *timer);

void Timer_Start(struct Timer *timer);

#endif // TIMER_H
