#include <USART.h>


void USART_DefaultHandler(void) {}

void (*USART1_Handler) (void) = USART_DefaultHandler;
void (*USART2_Handler) (void) = USART_DefaultHandler;
void (*USART3_Handler) (void) = USART_DefaultHandler;

void USART_Init(struct USART *usart) {
	switch ((int) usart->usart) {
		case (int) USART1:
			BITMASK_SET(RCC->APB2ENR, RCC_APB2ENR_USART1EN);
			usart->gpio_tx.gpio = GPIOA;
			usart->gpio_tx.pin = 9;
			usart->gpio_rx.gpio = GPIOA;
			usart->gpio_rx.pin = 10;
			break;
		case (int) USART2:
			BITMASK_SET(RCC->APB1ENR, RCC_APB1ENR_USART2EN);
			usart->gpio_tx.gpio = GPIOA;
			usart->gpio_tx.pin = 2;
			usart->gpio_rx.gpio = GPIOA;
			usart->gpio_rx.pin = 3;
			break;
		case (int) USART3:
			BITMASK_SET(RCC->APB1ENR, RCC_APB1ENR_USART3EN);
			usart->gpio_tx.gpio = GPIOB;
			usart->gpio_tx.pin = 10;
			usart->gpio_rx.gpio = GPIOB;
			usart->gpio_rx.pin = 11;
			break;
	}
	
	usart->gpio_tx.mode = GPIO_MODE_OUT_ALT_PUSH_PULL;
	usart->gpio_rx.mode = GPIO_MODE_IN_FLOATING;
	
	if (BIT_CHECK(usart->direction, USART_DIRECTION_RX)) {
		GPIO_Init(&usart->gpio_rx);
	}
	if (BIT_CHECK(usart->direction, USART_DIRECTION_TX)) {
		GPIO_Init(&usart->gpio_tx);
	}
	
	BITMASK_SETV(usart->usart->CR1, USART_CR1_M, usart->word_lenght);
	BITMASK_SETV(usart->usart->CR1, USART_CR1_PCE, usart->parity_control);
	BITMASK_SETV(usart->usart->CR1, USART_CR1_PS, usart->parity_selection);
	BITMASK_SETV(usart->usart->CR1, USART_CR1_TE | USART_CR1_RE, usart->direction);
	BITMASK_SETV(usart->usart->CR2, USART_CR2_STOP, usart->stop);
	
	uint32_t base_frequ = 0;
	switch ((int) usart->usart) {
		case (int) USART1:
			base_frequ = get_pclk2_freq();
			break;
		case (int) USART2:
			base_frequ = get_pclk1_freq();
			break;
		case (int) USART3:
			base_frequ = get_pclk1_freq();
			break;
	}
	
	uint32_t usart_div = base_frequ / usart->bauds;
	BITMASK_SETV(usart->usart->BRR, USART_BRR_DIV_Fraction | USART_BRR_DIV_Mantissa, usart_div);	
}

void USART_Start(struct USART *usart) {
	BITMASK_SET(usart->usart->CR1, USART_CR1_UE);
}


void USART_Send(struct USART *usart, uint8_t *msg, uint32_t len) {
	for(uint32_t i = 0; i < len; i++){
		BITMASK_SETV(usart->usart->DR, USART_DR_DR, msg[i]);
		while(!BITMASK_CHECK_ALL(usart->usart->SR, USART_SR_TXE));
	}
}

void USART_Attach_Receive_Interrupt(struct USART *usart, void (*function) (void), uint8_t priority) {
	switch ((int) usart->usart) {
		case (int) USART1:
			NVIC_EnableIRQ(USART1_IRQn);
			NVIC_SetPriority(USART1_IRQn, priority);
			USART1_Handler = function;
			break;
		case (int) USART2:
			NVIC_EnableIRQ(USART2_IRQn);
			NVIC_SetPriority(USART2_IRQn, priority);
			USART2_Handler = function;
			break;
		case (int) USART3:
			NVIC_EnableIRQ(USART3_IRQn);
			NVIC_SetPriority(USART3_IRQn, priority);
			USART3_Handler = function;
			break;
	}
	BITMASK_SET(usart->usart->CR1, USART_CR1_RXNEIE | USART_CR1_PEIE);
}

void USART1_IRQHandler(void) {
	int i = 0;
	i += 1;
}

void USART2_IRQHandler(void) {
}

void USART3_IRQHandler(void) {
}
