#include "MyADC.h"


void ADC_set_conversion_sequence(ADC_TypeDef * ADC, char * sequence, char count) {
	ADC->SQR1 = 0;
	ADC->SQR2 = 0;
	ADC->SQR3 = 0;
	ADC->SQR1 = count << 20;
	int i = 0;
	int offset = 0;
	while(i < count && i < 6) {
		ADC->SQR3 |= sequence[i] << offset;
		offset += 5;
	}
	offset = 0;
	while(i < count && i < 12) {
		ADC->SQR2 |= sequence[i] << offset;
		offset += 5;
	}
	offset = 0;
	while(i < count && i < 16) {
		ADC->SQR1 |= sequence[i] << offset;
		offset += 5;
	}
}

void ADC_set_sample_time(ADC_TypeDef *ADC, char channel, char sample_time) {
	if(channel > 9) {
		char offset = (channel - 9) * 3;
		ADC->SMPR1 = (ADC->SMPR1 & 0x7 << offset) | sample_time << offset;
	} else {
		char offset = channel * 3;
		ADC->SMPR2 = (ADC->SMPR2 & 0x7 << offset) | sample_time << offset;
	}
}