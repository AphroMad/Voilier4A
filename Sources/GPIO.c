#include <GPIO.h>

void GPIO_EXTIx_DefaultHandler(void) {}

void (*GPIO_EXTI0_Handler) (void) = GPIO_EXTIx_DefaultHandler;
void (*GPIO_EXTI1_Handler) (void) = GPIO_EXTIx_DefaultHandler;
void (*GPIO_EXTI2_Handler) (void) = GPIO_EXTIx_DefaultHandler;
void (*GPIO_EXTI3_Handler) (void) = GPIO_EXTIx_DefaultHandler;
void (*GPIO_EXTI4_Handler) (void) = GPIO_EXTIx_DefaultHandler;

const uint8_t GPIO_Mode_Conf[8] = {
	0x4,
	0x8,
	0x8,
	0x0,
	0x7,
	0x3,
	0xF,
	0xB,
};

void GPIO_Init(struct GPIO *gpio) {
	// Activation de l'horloge associée au port
	switch ((int) gpio->gpio) {
		case (int) GPIOA:
			BITMASK_SET(RCC->APB2ENR, RCC_APB2ENR_IOPAEN);
			break;
		case (int) GPIOB:
			BITMASK_SET(RCC->APB2ENR, RCC_APB2ENR_IOPBEN);
			break;
		case (int) GPIOC:
			BITMASK_SET(RCC->APB2ENR, RCC_APB2ENR_IOPCEN);
			break;
		case (int) GPIOD:
			BITMASK_SET(RCC->APB2ENR, RCC_APB2ENR_IOPDEN);
			break;
		case (int) GPIOE:
			BITMASK_SET(RCC->APB2ENR, RCC_APB2ENR_IOPEEN);
			break;
	}
	
	// Ecriture de la configuration du pin au bon registre
	if (gpio->pin > 7) {
		uint8_t offset = (gpio->pin - 8) * 4;
		BITMASK_SETV(gpio->gpio->CRH, 0xF << offset, GPIO_Mode_Conf[gpio->mode] << offset);
	} else {
		uint8_t offset = gpio->pin * 4;
		BITMASK_SETV(gpio->gpio->CRL, 0xF << offset, GPIO_Mode_Conf[gpio->mode] << offset);
	}
	
	// Si on est en input pull up/down on défini le bon niveau de sortie
	switch (gpio->mode) {
		case GPIO_MODE_IN_PULL_DOWN:
			GPIO_Set(gpio, 0);
			break;
		case GPIO_MODE_IN_PULL_UP:
			GPIO_Set(gpio, 1);
			break;
		default:
			break;
	}
}

void GPIO_Set(struct GPIO *gpio, uint8_t level) {
	BIT_SETV(gpio->gpio->BSRR, gpio->pin, level);
}

void GPIO_Attach_Interrupt(struct GPIO *gpio, void (*function) (void), uint8_t priority, enum GPIO_Interrupt_Mode mode) {
	// Activation de l'horloge pour AFIO
	BITMASK_SET(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);
	// Activation des interruptions pour la ligne associée au pin
	BIT_SET(EXTI->IMR, gpio->pin);
	switch (mode) {
		case GPIO_INTERRUPT_MODE_RISING:
			BIT_SET(EXTI->RTSR, gpio->pin);
			break;
		case GPIO_INTERRUPT_MODE_FALLING:
			BIT_SET(EXTI->FTSR, gpio->pin);
			break;
		case GPIO_INTERRUPT_MODE_BOTH:
			BIT_SET(EXTI->FTSR, gpio->pin);
			BIT_SET(EXTI->RTSR, gpio->pin);
			break;
	};
	
	// Choix du port dans la configuration de l'interruption
	uint32_t EXTI_CR1 = 0;
	uint32_t EXTI_CR2 = 0;
	switch ((int) gpio->gpio) {
		case (int) GPIOA:
			EXTI_CR1 = AFIO_EXTICR1_EXTI0_PA | AFIO_EXTICR1_EXTI1_PA | AFIO_EXTICR1_EXTI2_PA | AFIO_EXTICR1_EXTI3_PA;
			EXTI_CR2 = AFIO_EXTICR2_EXTI4_PA;
			break;
		case (int) GPIOB:
			EXTI_CR1 = AFIO_EXTICR1_EXTI0_PB | AFIO_EXTICR1_EXTI1_PB | AFIO_EXTICR1_EXTI2_PB | AFIO_EXTICR1_EXTI3_PB;
			EXTI_CR2 = AFIO_EXTICR2_EXTI4_PB;
			break;
		case (int) GPIOC:
			EXTI_CR1 = AFIO_EXTICR1_EXTI0_PC | AFIO_EXTICR1_EXTI1_PC | AFIO_EXTICR1_EXTI2_PC | AFIO_EXTICR1_EXTI3_PC;
			EXTI_CR2 = AFIO_EXTICR2_EXTI4_PC;
			break;
		case (int) GPIOD:
			EXTI_CR1 = AFIO_EXTICR1_EXTI0_PD | AFIO_EXTICR1_EXTI1_PD | AFIO_EXTICR1_EXTI2_PD | AFIO_EXTICR1_EXTI3_PD;
			EXTI_CR2 = AFIO_EXTICR2_EXTI4_PD;
			break;
		case (int) GPIOE:
			EXTI_CR1 = AFIO_EXTICR1_EXTI0_PE | AFIO_EXTICR1_EXTI1_PE | AFIO_EXTICR1_EXTI2_PE | AFIO_EXTICR1_EXTI3_PE;
			EXTI_CR2 = AFIO_EXTICR2_EXTI4_PE;
			break;
	}
	
	switch (gpio->pin) {
		case 0:
			BITMASK_SETV(AFIO->EXTICR[0], AFIO_EXTICR1_EXTI0, EXTI_CR1);
			break;
		case 1:
			BITMASK_SETV(AFIO->EXTICR[0], AFIO_EXTICR1_EXTI1, EXTI_CR1);
			break;
		case 2:
			BITMASK_SETV(AFIO->EXTICR[0], AFIO_EXTICR1_EXTI2, EXTI_CR1);
			break;
		case 3:
			BITMASK_SETV(AFIO->EXTICR[0], AFIO_EXTICR1_EXTI3, EXTI_CR1);
			break;
		case 4:
			BITMASK_SETV(AFIO->EXTICR[0], AFIO_EXTICR2_EXTI4, EXTI_CR2);
			break;
		default:
			break;
	}
	
	
	// Activation de l'interruption au niveau NVIC
	switch (gpio->pin) {
		case 0:
			NVIC_EnableIRQ(EXTI0_IRQn);
			NVIC_SetPriority(EXTI0_IRQn, priority);
			GPIO_EXTI0_Handler = function;
			break;
		case 1:
			NVIC_EnableIRQ(EXTI1_IRQn);
			NVIC_SetPriority(EXTI1_IRQn, priority);
			GPIO_EXTI1_Handler = function;
			break;
		case 2:
			NVIC_EnableIRQ(EXTI2_IRQn);
			NVIC_SetPriority(EXTI2_IRQn, priority);
			GPIO_EXTI2_Handler = function;
			break;
		case 3:
			NVIC_EnableIRQ(EXTI3_IRQn);
			NVIC_SetPriority(EXTI3_IRQn, priority);
			GPIO_EXTI3_Handler = function;
			break;
		case 4:
			NVIC_EnableIRQ(EXTI4_IRQn);
			NVIC_SetPriority(EXTI4_IRQn, priority);
			GPIO_EXTI4_Handler = function;
			break;
	}
	
	
}

void EXTI0_IRQHandler(void) {
	GPIO_EXTI0_Handler();
	BIT_SET(EXTI->PR, 0);
}

void EXTI1_IRQHandler(void) {
	GPIO_EXTI1_Handler();
	BIT_SET(EXTI->PR, 1);
}

void EXTI2_IRQHandler(void) {
	GPIO_EXTI2_Handler();
	BIT_SET(EXTI->PR, 2);
}

void EXTI3_IRQHandler(void) {
	GPIO_EXTI3_Handler();
	BIT_SET(EXTI->PR, 3);
}

void EXTI4_IRQHandler(void) {
	GPIO_EXTI4_Handler();
	BIT_SET(EXTI->PR, 4);
}
