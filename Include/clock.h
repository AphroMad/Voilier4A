#ifndef CLOCK_H
#define CLOCK_H

#include <stm32f10x.h>
#include <utils.h>

uint32_t get_hpre_freq(void);
uint32_t get_pclk1_freq(void);
uint32_t get_pclk2_freq(void);

#endif // CLOCK_H
