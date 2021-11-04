#include <ADC.h>


void ADC_Init(void) {
	BITMASK_SET(RCC->APB2ENR, RCC_APB2ENR_ADC1EN);
	BITMASK_SET(RCC->CFGR, RCC_CFGR_ADCPRE_DIV6);
	BITMASK_SET(ADC1->CR2, ADC_CR2_ADON);
}

void ADC_Pin_Init(enum ADC_PIN pin) {
	if (pin < 16) {
		struct GPIO gpio = {
			.mode = GPIO_MODE_IN_ANALOG,
		};
		if (pin < 8) {
			gpio.gpio = GPIOA;
			gpio.pin = pin;
		} else if (pin < 10) {
			gpio.gpio = GPIOB;
			gpio.pin = pin - 8;
		} else if (pin < 16) {
			gpio.gpio = GPIOC;
			gpio.pin = pin - 10;
		}
		GPIO_Init(&gpio);
	} else {
		BITMASK_SET(ADC1->CR2, ADC_CR2_TSVREFE);
	}
}

uint16_t ADC_Pin_Mesure(enum ADC_PIN pin) {
	
	BITMASK_CLEAR(ADC1->SQR1, ADC_SQR1_L);
	BITMASK_SETV(ADC1->SQR3, ADC_SQR3_SQ1, pin);
	// Lancement de la conversion
	BITMASK_SET(ADC1->CR2, ADC_CR2_ADON);
	
	// Attente de la fin de conversion
	while(BITMASK_CHECK_ALL(ADC1->SR, ADC_SR_EOC) == 0);
	BITMASK_CLEAR(ADC1->SR, ADC_SR_EOC);
	ADC1->SR &= ~ADC_SR_EOC;
		
	return BITMASK_GET(ADC1->DR, ADC_DR_DATA);
}
