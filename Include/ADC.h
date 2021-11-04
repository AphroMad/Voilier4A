#ifndef ADC_H
#define ADC_H

#include <utils.h>
#include <GPIO.h>

enum ADC_PIN {
	ADC_PA0 = 0,
	ADC_PA1 = 1,
	ADC_PA2 = 2,
	ADC_PA3 = 3,
	ADC_PA4 = 4,
	ADC_PA5 = 5,
	ADC_PA6 = 6,
	ADC_PA7 = 7,
	ADC_PB0 = 8,
	ADC_PB1 = 9,
	ADC_PC0 = 10,
	ADC_PC1 = 11,
	ADC_PC2 = 12,
	ADC_PC3 = 13,
	ADC_PC4 = 14,
	ADC_PC5 = 15,
	ADC_TEMPERATURE = 16,
	ADC_VREF = 17
};

void ADC_Init(void);
void ADC_Pin_Init(enum ADC_PIN pin);
uint16_t ADC_Pin_Mesure(enum ADC_PIN pin);

#endif // ADC_H
