#include "MyTimer.h"
#include "MyGPIO.h"

void (*MyTimer_TIM1_Handler) (void) = MyTimer_DefaultHandler;
void (*MyTimer_TIM2_Handler) (void) = MyTimer_DefaultHandler;
void (*MyTimer_TIM3_Handler) (void) = MyTimer_DefaultHandler;
void (*MyTimer_TIM4_Handler) (void) = MyTimer_DefaultHandler;

void MyTimer_Base_Init(MyTimer_Struct_TypeDef * Timer) {
	switch ((int)Timer->Timer) {
		case (int)TIM1:
				RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
				break;
		case (int)TIM2:
				RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
				break;
		case (int)TIM3:
				RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
				break;
		case (int)TIM4:
				RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
				break;
	}
	
	Timer->Timer->ARR = Timer->ARR;
	Timer->Timer->PSC = Timer->PSC;

}

void MyTimer_DefaultHandler() {}

void MyTimer_ActiveIT(TIM_TypeDef * Timer, char Prio, void (*IT_function) (void)) {
	Timer->DIER |= 0x01;
	switch ((int) Timer) {
		case (int)TIM1:
				NVIC_EnableIRQ(TIM1_UP_IRQn);
				NVIC_SetPriority(TIM1_UP_IRQn, Prio);
				MyTimer_TIM1_Handler = IT_function;
				break;
		case (int)TIM2:
				NVIC_EnableIRQ(TIM2_IRQn);
				NVIC_SetPriority(TIM2_IRQn, Prio);
				MyTimer_TIM2_Handler = IT_function;
				break;
		case (int)TIM3:
				NVIC_EnableIRQ(TIM3_IRQn);
				NVIC_SetPriority(TIM3_IRQn, Prio);
				MyTimer_TIM3_Handler = IT_function;
				break;
		case (int)TIM4:
				NVIC_EnableIRQ(TIM4_IRQn);
				NVIC_SetPriority(TIM4_IRQn, Prio);
				MyTimer_TIM4_Handler = IT_function;
				break;
	}
}

void TIM1_UP_IRQHandler(void) {
	MyTimer_TIM1_Handler();
	TIM1->SR &= ~0x01;
}


void TIM2_IRQHandler(void) {
	MyTimer_TIM2_Handler();
	TIM2->SR &= ~0x01;
}

void TIM3_IRQHandler(void) {
	MyTimer_TIM3_Handler();
	TIM3->SR &= ~0x01;
}

void TIM4_IRQHandler(void) {
	MyTimer_TIM4_Handler();
	TIM4->SR &= ~0x01;
}

void MyTimer_PWM(TIM_TypeDef * Timer ,char Channel) {
	switch (Channel) {
		case 1:
			Timer->CCER |= TIM_CCER_CC1E;
			Timer->CCMR1 &= ~TIM_CCMR1_CC1S;
			Timer->CCMR1 = (Timer->CCMR1 & ~TIM_CCMR1_OC1M) | 0x60;
			break;
		case 2:
			Timer->CCER |= TIM_CCER_CC2E;
			Timer->CCMR1 &= ~TIM_CCMR1_CC2S;
			Timer->CCMR1 = (Timer->CCMR1 & ~TIM_CCMR1_OC2M) | 0x6000;
			break;
		case 3:
			Timer->CCER |= TIM_CCER_CC3E;
			Timer->CCMR2 &= ~TIM_CCMR2_CC3S;
			Timer->CCMR2 = (Timer->CCMR2 & ~TIM_CCMR2_OC3M) | 0x60;
			break;
		case 4:
			Timer->CCER |= TIM_CCER_CC4E;
			Timer->CCMR2 &= ~TIM_CCMR2_CC4S;
			Timer->CCMR2 = (Timer->CCMR2 & ~TIM_CCMR2_OC4M) | 0x6000; 
			break;
	}
	if(Timer == TIM1) {
		Timer->BDTR |= TIM_BDTR_AOE;
	}
}
