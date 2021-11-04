#include <PWM.h>


void PWM_set_timer(struct PWM *pwm) {
	switch ((int) pwm->gpio.gpio) {
		case (int) GPIOA:
			switch (pwm->gpio.pin) {
				case 0:
				case 1:
				case 2:
				case 3:
					pwm->timer.timer = TIM2;
					pwm->channel = pwm->gpio.pin + 1; // PA0 = 1, PA1 = 2, PA2 = 3, PA3 = 4
					break;
				case 6:
				case 7:
					pwm->timer.timer = TIM3;
					pwm->channel = pwm->gpio.pin - 5; // PA6 = 1, PA7 = 2
					break;
				case 8:
				case 9:
				case 10:
				case 11:
					pwm->timer.timer = TIM1;
					pwm->channel = pwm->gpio.pin - 7; // PA8 = 1, PA9 = 2, PA10 = 3, PA11 = 4
					break;
				default:
					break;
			}
			break;
		case (int) GPIOB:
			switch (pwm->gpio.pin) {
				case 0:
				case 1:
					pwm->timer.timer = TIM3;
					pwm->channel = pwm->gpio.pin + 3; // PB0 = 3, PB1 = 4
					break;
				case 6:
				case 7:
				case 8:
				case 9:
					pwm->timer.timer = TIM4;
					pwm->channel = pwm->gpio.pin - 5; // PB6 = 1, PB7 = 2, PB8 = 3, PB9 = 4
			}
			break;
		default:
			break;
	}
}


void PWM_Init(struct PWM *pwm) {
	if ((pwm->gpio.mode != GPIO_MODE_OUT_ALT_PUSH_PULL) && (pwm->gpio.mode != GPIO_MODE_OUT_ALT_OPEN_DRAIN)) {
		// Le mode du gpio n'est pas un alt, on assume que le comportement voulu est push_pull
		pwm->gpio.mode = GPIO_MODE_OUT_ALT_PUSH_PULL;
	}
	PWM_set_timer(pwm);
	
	GPIO_Init(&pwm->gpio);
	Timer_Init(&pwm->timer);
	
	switch (pwm->channel) {
		case 1:
			BITMASK_SET(pwm->timer.timer->CCER, TIM_CCER_CC1E);
			BITMASK_CLEAR(pwm->timer.timer->CCMR1, TIM_CCMR1_CC1S);
			BITMASK_SETV(pwm->timer.timer->CCMR1, TIM_CCMR1_OC1M, TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);
			break;
		case 2:
			BITMASK_SET(pwm->timer.timer->CCER, TIM_CCER_CC2E);
			BITMASK_CLEAR(pwm->timer.timer->CCMR1, TIM_CCMR1_CC2S);
			BITMASK_SETV(pwm->timer.timer->CCMR1, TIM_CCMR1_OC2M, TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2);
			break;
		case 3:
			BITMASK_SET(pwm->timer.timer->CCER, TIM_CCER_CC3E);
			BITMASK_CLEAR(pwm->timer.timer->CCMR2, TIM_CCMR2_CC3S);
			BITMASK_SETV(pwm->timer.timer->CCMR2, TIM_CCMR2_OC3M, TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2);
			break;
		case 4:
			BITMASK_SET(pwm->timer.timer->CCER, TIM_CCER_CC4E);
			BITMASK_CLEAR(pwm->timer.timer->CCMR2, TIM_CCMR2_CC4S);
			BITMASK_SETV(pwm->timer.timer->CCMR2, TIM_CCMR2_OC4M, TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2);
			break;
	}
	
	if (pwm->timer.timer == TIM1) {
		BITMASK_SET(TIM1->BDTR, TIM_BDTR_AOE);
	}
}

void PWM_Set(struct PWM *pwm, uint16_t level) {
	switch (pwm->channel) {
		case 1:
			pwm->timer.timer->CCR1 = level;
			break;
		case 2:
			pwm->timer.timer->CCR2 = level;
			break;
		case 3:
			pwm->timer.timer->CCR3 = level;
			break;
		case 4:
			pwm->timer.timer->CCR4 = level;
			break;
	}
}

void PWM_Start(struct PWM *pwm) {
	Timer_Start(&pwm->timer);
}
