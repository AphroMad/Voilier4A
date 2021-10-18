#ifndef MYADC_H
#define MYADC_H

#include "stm32f10x.h"

#define ADC_PA0  0
#define ADC_PA1  1
#define ADC_PA2  2
#define ADC_PA3  3
#define ADC_PA4  4
#define ADC_PA5  5
#define ADC_PA6  6
#define ADC_PA7  7
#define ADC_PB0  8
#define ADC_PB1  9
#define ADC_PC0 10
#define ADC_PC1 11
#define ADC_PC2 12
#define ADC_PC3 13
#define ADC_PC4 14
#define ADC_PC5 15
#define ADC_TEMPERATURE 16
#define ADC_VREF 17

#define ADC_TRIGGER_REGULAR_TIM1_CC1  0x00000
#define ADC_TRIGGER_REGULAR_TIM1_CC2  0x20000
#define ADC_TRIGGER_REGULAR_TIM1_CC3  0x40000
#define ADC_TRIGGER_REGULAR_TIM2_CC2  0x60000
#define ADC_TRIGGER_REGULAR_TIM3_TRGO 0x80000
#define ADC_TRIGGER_REGULAR_TIM4_CC4  0xa0000
#define ADC_TRIGGER_REGULAR_EXTI      0xc0000
#define ADC_TRIGGER_REGULAR_SWSTART   0xe0000

#define ADC_SAMPLE_TIME_1_5 0x0
#define ADC_SAMPLE_TIME_7_5 0x1
#define ADC_SAMPLE_TIME_13_5 0x2
#define ADC_SAMPLE_TIME_28_5 0x3
#define ADC_SAMPLE_TIME_41_5 0x4
#define ADC_SAMPLE_TIME_55_5 0x5
#define ADC_SAMPLE_TIME_71_5 0x6
#define ADC_SAMPLE_TIME_239_5 0x7

// Enable ADC
#define ADC_enable(ADC) (ADC->CR2 |= ADC_CR2_ADON; RCC->APB2ENR|=RCC_APB2ENR_ADC1EN; RCC->CFGR|=RCC_CFGR_ADCPRE_DIV6)
#define ADC_disable(ADC) (ADC->CR2 |= ADC_CR2_ADON)
// Set conversion sequence
void ADC_set_conversion_sequence(ADC_TypeDef * ADC, char * sequence, char count);

// Enable temperature and verf input on channels 16 and 17
#define ADC_enable_temperature_vref(ADC) (ADC->CR2 |= ADC_CR2_TSVREFE);
#define ADC_disable_temperature_vref(ADC) (ADC->CR2 &= ADC_CR2_TSVREFE);
// Enable external trigger for ADC
#define ADC_enable_external_trigger(ADC, trigger) (ADC->CR2 = ADC_CR2_EXTTRIG | (ADC->CR2 & ~0xe0000) | trigger)
// Start conversion for regular sequence
#define ADC_start_conversion(ADC) (ADC->CR2 |= ADC_CR2_SWSTART)
// Start conversion for injected sequence
#define ADC_start_injected_conversion(ADC) (ADC->CR2 |= ADC_CR2_JSWSTART)
// Set watchdog channel
#define ADC_enable_watchdog(ADC) (ADC->CR1 |= ADC_CR1_AWDEN)
#define ADC_disable_watchdog(ADC) (ADC->CR1 &= ~ADC_CR1_AWDEN)
#define ADC_set_watchdog(ADC, channel) (ADC->CR2 |= (ADC->CR2 & ~0x1f) | channel)
#define ADC_set_watchdog_high_threshold(ADC, value) (ADC->ADC_HTR = value)
#define ADC_set_watchdog_low_threshold(ADC, value) (ADC->ADC_LTR = value)
// Continuous mode conversion
#define ADC_enable_couninuous(ADC) (ADC->CR2 |= ADC_CR2_CONT)
#define ADC_disable_continous(ADC) (ADC->CR2 &= ~ADC_CR2_CONT)
// Set sample time for a specific channel
void ADC_set_sample_time(ADC_TypeDef *ADC, char channel, char sample_time);


// ADC_CR1
//    AWDEN   Analog watchdog regular channels
//    JAWDEN  Analog watchdog injected channels
//    DUALMOD Dual mode selection
//    DISCNUM Discontinuous channel count
//    JDISCEN enable discontinuous mode on injected
//    DISCEN  enable discontinuous mode on regular
//    JEOCIE	interupt fin conversion injected
//    AWDIE   Analog watchdog interupt enable
//    EOCIE   enable Interupt pour EOC
//    AWDCH   Channel pour watchdog

// ADC_CR2~e
//    EXTTRIG  enable external trigger for regular
//    EXTSEL   external trigger selection regular
//    JEXTTRIG enable external trigger for injected
//    JEXTSEL  external trigger selection inkected
//    ALIGN    data alignement
//    DMA      dma enable
//    RSTCAL   reset calibration - reset when finished
//    CAL      start calibration - reset when finished
//    CONT     continuous mode
//    ADON     adc enable

// ADC_JOFRx (x \in 1..=4)
//    JOFFSETx offset à soustraire de la valeur lue lors de la lecture des injected



// ADC_SQR1
// ADC_SQR2
// ADC SQR3
//    L Longeur de la séquence regular
//    SQx conversion numéro x

// ADC_JSQR
//    JL Longueur de la séquence injected
//    JSQx conversion numéro x (Attention, remplissage "à l'envers" 4 / 3-4 / 2-3-4 / 1-2-3-4

// ADC_JDRx
//    Lecture injected x

// ADC_DR
//    Lecture regular

#endif // MYADC_C