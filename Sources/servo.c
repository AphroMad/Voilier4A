#include <servo.h>

void Servo_Init(struct Servo *servo) {
	PWM_Init(&servo->pwm);
}

void Servo_Set(struct Servo *servo, uint16_t angle) {
	PWM_Set(&servo->pwm, MAP(angle, servo->min, servo->max, servo->arr_min, servo->arr_max));
}

void Servo_Start(struct Servo *servo) {
	PWM_Start(&servo->pwm);
}
