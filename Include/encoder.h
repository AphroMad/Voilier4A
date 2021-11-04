#ifndef ENCODER_H
#define ENCODER_H

#include <stm32f10x.h>
#include <utils.h>
#include <timer.h>
#include <GPIO.h>

enum Encoder_Polarity {
	ENCODER_POLARITY_RISING,
	ENCODER_POLARITY_FALLING,
	ENCODER_POLARITY_BOTH,
};

struct Encoder {
	struct Timer timer;
	enum Encoder_Polarity polarity;
	struct GPIO gpio_a;
	struct GPIO gpio_b;
	struct GPIO gpio_reset;
};

void Encoder_Init(struct Encoder *encoder);

void Encoder_Start(struct Encoder *encoder);

#endif // ENCODER_H
