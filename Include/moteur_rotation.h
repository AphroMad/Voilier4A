#ifndef MOTEUR_ROTATION_H
#define MOTEUR_ROTATION_H

#include <GPIO.h>
#include <PWM.h>

/*!
 * Structure d�finissant tous les param�tres du moteur de rotation
 *
 * Tous les champs ne sont pas n�cessaire � d�finir, le minimum est: .gpio_orientation.gpio, .gpio_orientation.pin,
 * .pwm_vitesse.gpio.gpio, .pwm_vitesse.gpio.pin, .pwm_vitesse.timer.arr, .pwm_vitesse.timer.psc
 */
struct MoteurRotation {
	struct GPIO gpio_orientation;
	struct PWM pwm_vitesse;
};

/*!
 * Initialisation du moteur et des GPIO associ�s
 */
void MoteurRotation_Init(struct MoteurRotation *moteur_rotation);

/*!
 * D�finition d'une vitesse de rotation relativement � .pwm_vitesse.arr
 */
void MoteurRotation_Set(struct MoteurRotation *moteur_rotation, uint8_t orientation, uint8_t level);


void MoteurRotation_Start(struct MoteurRotation *moteur_rotation);

#endif // MOTEUR_ROTATION_H
