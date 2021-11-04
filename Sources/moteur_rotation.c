#include <moteur_rotation.h>

void MoteurRotation_Init(struct MoteurRotation *moteur_rotation) {
	moteur_rotation->gpio_orientation.mode = GPIO_MODE_OUT_PUSH_PULL;
	moteur_rotation->pwm_vitesse.gpio.mode = GPIO_MODE_OUT_ALT_PUSH_PULL;
	
	GPIO_Init(&moteur_rotation->gpio_orientation);
	PWM_Init(&moteur_rotation->pwm_vitesse);
}

void MoteurRotation_Set(struct MoteurRotation *moteur_rotation, uint8_t orientation, uint8_t level) {
	GPIO_Set(&moteur_rotation->gpio_orientation, orientation);
	PWM_Set(&moteur_rotation->pwm_vitesse, MAP(level, 0, 100, 0, moteur_rotation->pwm_vitesse.timer.arr));
	GPIO_Set(&moteur_rotation->gpio_orientation, orientation);
}

void MoteurRotation_Start(struct MoteurRotation *moteur_rotation) {
	PWM_Start(&moteur_rotation->pwm_vitesse);
}
