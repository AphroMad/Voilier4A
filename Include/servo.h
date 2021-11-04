#ifndef SERVO_H
#define SERVO_H

#include <PWM.h>

struct Servo {
	struct PWM pwm;
	uint16_t min;
	uint16_t max;
	uint16_t arr_min;
	uint16_t arr_max;
};

void Servo_Init(struct Servo *servo);

void Servo_Set(struct Servo *servo, uint16_t angle);

void Servo_Start(struct Servo *servo);

#endif // SERVO_H
