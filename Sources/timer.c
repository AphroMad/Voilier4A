#include <timer.h>

void Timer_Init(struct Timer *timer) {
	switch ((int) timer->timer) {
		case (int) TIM1:
			BITMASK_SET(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);
			break;
		case (int) TIM2:
			BITMASK_SET(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);
			break;
		case (int) TIM3:
			BITMASK_SET(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);
			break;
		case (int) TIM4:
			BITMASK_SET(RCC->APB1ENR, RCC_APB1ENR_TIM4EN);
			break;
	}
	
	timer->timer->ARR = timer->arr;
	timer->timer->PSC = timer->psc;
	BITMASK_SETV(timer->timer->SMCR, TIM_SMCR_SMS, timer->slave_mode);
}

void Timer_Start(struct Timer *timer) {
	BITMASK_SET(timer->timer->CR1, TIM_CR1_CEN);
}
