#include <encoder.h>


void Encoder_Interrupt_Reset_TIM1(void) {
	TIM1->CNT = 0;
}

void Encoder_Interrupt_Reset_TIM2(void) {
	TIM2->CNT = 0;
}

void Encoder_Interrupt_Reset_TIM3(void) {
	TIM3->CNT = 0;
}

void Encoder_Interrupt_Reset_TIM4(void) {
	TIM4->CNT = 0;
}


void Encoder_Init(struct Encoder *encoder) {
	if ((encoder->timer.slave_mode != TIMER_SLAVE_MODE_ENCODER_1) 
		&& (encoder->timer.slave_mode != TIMER_SLAVE_MODE_ENCODER_2)
		&& (encoder->timer.slave_mode != TIMER_SLAVE_MODE_ENCODER_3)) {
		// Le mode du gpio n'est pas un alt, on assume que le mode voulu est ENCODER_3
		encoder->timer.slave_mode = TIMER_SLAVE_MODE_ENCODER_3;
	}
	
	Timer_Init(&encoder->timer);
	// Initialisation des channels 1 et 2 en mode input
	BITMASK_SETV(encoder->timer.timer->CCMR1, TIM_CCMR1_CC1S | TIM_CCMR1_CC2S, TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0);
	// Initialisation de la parité
	BITMASK_SETV(encoder->timer.timer->CCER, TIM_CCER_CC1P | TIM_CCER_CC2P, encoder->polarity | encoder->polarity << 4);
	BITMASK_CLEAR(encoder->timer.timer->SMCR, TIM_SMCR_ECE);

	encoder->gpio_a.mode = GPIO_MODE_IN_FLOATING;
	encoder->gpio_b.mode = GPIO_MODE_IN_FLOATING;
	switch ((int) encoder->timer.timer) {
		case (int) TIM1:
			encoder->gpio_a.gpio = GPIOA;
			encoder->gpio_a.pin = 8;
			encoder->gpio_b.gpio = GPIOA;
			encoder->gpio_b.pin = 9;
			break;
		case (int) TIM2:
			encoder->gpio_a.gpio = GPIOA;
			encoder->gpio_a.pin = 0;
			encoder->gpio_b.gpio = GPIOA;
			encoder->gpio_b.pin = 1;
			break;
		case (int) TIM3:
			encoder->gpio_a.gpio = GPIOA;
			encoder->gpio_a.pin = 6;
			encoder->gpio_b.gpio = GPIOA;
			encoder->gpio_b.pin = 7;
			break;
		case (int) TIM4:
			encoder->gpio_a.gpio = GPIOB;
			encoder->gpio_a.pin = 6;
			encoder->gpio_b.gpio = GPIOB;
			encoder->gpio_b.pin = 7;
			break;
		default:
			break;
	}
	encoder->gpio_reset.mode = GPIO_MODE_IN_FLOATING;
	
	GPIO_Init(&encoder->gpio_a);
	GPIO_Init(&encoder->gpio_b);
	GPIO_Init(&encoder->gpio_reset);
	switch((int) encoder->timer.timer) {
		case (int) TIM1:
			GPIO_Attach_Interrupt(&encoder->gpio_reset, Encoder_Interrupt_Reset_TIM1, 8, GPIO_INTERRUPT_MODE_FALLING);
			break;
		case (int) TIM2:
			GPIO_Attach_Interrupt(&encoder->gpio_reset, Encoder_Interrupt_Reset_TIM2, 8, GPIO_INTERRUPT_MODE_FALLING);
			break;
		case (int) TIM3:
			GPIO_Attach_Interrupt(&encoder->gpio_reset, Encoder_Interrupt_Reset_TIM3, 8, GPIO_INTERRUPT_MODE_FALLING);
			break;
		case (int) TIM4:
			GPIO_Attach_Interrupt(&encoder->gpio_reset, Encoder_Interrupt_Reset_TIM4, 8, GPIO_INTERRUPT_MODE_FALLING);
			break;
	}
}

void Encoder_Start(struct Encoder *encoder) {
	// TODO: Vérifier si c'est nécessaire d'activer le timer avant de définir le SMS
	BITMASK_CLEAR(encoder->timer.timer->SMCR, TIM_SMCR_SMS);
	Timer_Start(&encoder->timer);
	BITMASK_SET(encoder->timer.timer->SMCR, TIMER_SLAVE_MODE_ENCODER_3);
}
