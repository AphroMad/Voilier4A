#ifndef PWM_H
#define PWM_H

#include <stm32f10x.h>
#include <GPIO.h>
#include <timer.h>
#include <utils.h>

/*!
 * Structure contenant tous les paramètres pour définir un PWM, utilisé en tant que premier argument des fonctions PWM_*
 * 
 * Tous les champs ne sont pas utiles, le minimum est gpio.gpio, gpio.pin, timer.arr, timer.psc
 * 
 * Attention, il faut que le pin GPIO supporte le PWM, sinon les méthodes PWM_* auront un comportement indéfini
 */
struct PWM {
	struct GPIO gpio;
	struct Timer timer;
	uint16_t level;
	uint8_t channel;
};

void PWM_Init(struct PWM *pwm);


/*!
 * Définition de la valeur d'un PWM
 *
 * Le rapport cyclique est level / ARR
 */
void PWM_Set(struct PWM *pwm, uint16_t level);

void PWM_Start(struct PWM *pwm);

#endif // PWM_H
