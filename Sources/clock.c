#include <clock.h>

uint32_t get_hpre_freq(void) {
	uint32_t hpre_freq = 72000000;
	switch (BITMASK_GET(RCC->CFGR, RCC_CFGR_HPRE)) {
		case 0:
		case RCC_CFGR_HPRE_0:
		case RCC_CFGR_HPRE_1:
		case RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_0:
		case RCC_CFGR_HPRE_2:
		case RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_0:
		case RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_1:
		case RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_0:
			hpre_freq = 72000000;
			break;
		case RCC_CFGR_HPRE_3:
			hpre_freq = 36000000;
			break;
		case RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_0:
			hpre_freq = 18000000;
			break;
		case RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_1:
			hpre_freq = 9000000;
			break;
		case RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_0:
			hpre_freq = 4500000;
			break;
		case RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2:
			hpre_freq = 1125000;
			break;
		case RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_0:
			hpre_freq = 562500;
			break;
		case RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_1:
			hpre_freq = 281250;
			break;
		case RCC_CFGR_HPRE_3 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_0:
			hpre_freq = 140625;
			break;
	}
	return hpre_freq;
}

uint32_t get_pclk1_freq(void) {
	uint32_t hpre_freq = get_hpre_freq();
	uint32_t pclk1_freq = 0;
	
	switch (BITMASK_GET(RCC->CFGR, RCC_CFGR_PPRE1)) {
		case 0:
		case RCC_CFGR_PPRE1_0:
		case RCC_CFGR_PPRE1_1:
		case RCC_CFGR_PPRE1_1 | RCC_CFGR_PPRE1_0:
			pclk1_freq = hpre_freq;
			break;
		case RCC_CFGR_PPRE1_2:
			pclk1_freq = hpre_freq >> 1;
			break;
		case RCC_CFGR_PPRE1_2 | RCC_CFGR_PPRE1_0:
			pclk1_freq = hpre_freq >> 2;
			break;
		case RCC_CFGR_PPRE1_2 | RCC_CFGR_PPRE1_1:
			pclk1_freq = hpre_freq >> 3;
			break;
		case RCC_CFGR_PPRE1_2 | RCC_CFGR_PPRE1_1 | RCC_CFGR_PPRE1_0:
			pclk1_freq = hpre_freq >> 4;
			break;
	}
	
	return pclk1_freq;
}

uint32_t get_pclk2_freq(void) {
	uint32_t hpre_freq = get_hpre_freq();
	uint32_t pclk2_freq = 0;
	
	switch (BITMASK_GET(RCC->CFGR, RCC_CFGR_PPRE2)) {
		case 0:
		case RCC_CFGR_PPRE2_0:
		case RCC_CFGR_PPRE2_1:
		case RCC_CFGR_PPRE2_1 | RCC_CFGR_PPRE2_0:
			pclk2_freq = hpre_freq;
			break;
		case RCC_CFGR_PPRE2_2:
			pclk2_freq = hpre_freq >> 1;
			break;
		case RCC_CFGR_PPRE2_2 | RCC_CFGR_PPRE2_0:
			pclk2_freq = hpre_freq >> 2;
			break;
		case RCC_CFGR_PPRE2_2 | RCC_CFGR_PPRE2_1:
			pclk2_freq = hpre_freq >> 3;
			break;
		case RCC_CFGR_PPRE2_2 | RCC_CFGR_PPRE2_1 | RCC_CFGR_PPRE2_0:
			pclk2_freq = hpre_freq >> 4;
			break;
	}
	
	return pclk2_freq;
}
