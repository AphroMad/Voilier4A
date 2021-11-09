#ifndef USART_H
#define USART_H

#include <stm32f10x.h>
#include <utils.h>
#include <GPIO.h>
#include <clock.h>

enum USART_Word_Lenght {
	USART_WORD_LENGHT_8BITS = 0x0,
	USART_WORD_LENGHT_9BITS = USART_CR1_M,
};

enum USART_Parity_Control {
	USART_PARITY_CONTROL_DISABLED = 0x0,
	USART_PARITY_CONTROL_ENABLED = USART_CR1_PCE,
};

enum USART_Parity_Selection {
	USART_PARITY_EVEN = 0x0,
	USART_PARITY_ODD = USART_CR1_PS,
};

enum USART_Direction {
	USART_DIRECTION_NONE = 0x0,
	USART_DIRECTION_RX = USART_CR1_RE,
	USART_DIRECTION_TX = USART_CR1_TE,
	USART_DIRECTION_TX_RX = USART_CR1_RE | USART_CR1_TE,
};

enum USART_Stop {
	USART_STOP_1 = 0x0,
	USART_STOP_0_5 = USART_CR2_STOP_0,
	USART_STOP_2 = USART_CR2_STOP_1,
	USART_STOP_1_5 = USART_CR2_STOP_0 | USART_CR2_STOP_1,
};

struct USART {
	USART_TypeDef *usart;
	struct GPIO gpio_tx;
	struct GPIO gpio_rx;
	struct GPIO gpio_cts;
	enum USART_Word_Lenght word_lenght;
	enum USART_Parity_Control parity_control;
	enum USART_Parity_Selection parity_selection;
	enum USART_Direction direction;
	enum USART_Stop stop;
	uint16_t bauds;
};

void USART_Init(struct USART *config);
void USART_Start(struct USART *config);
void USART_Send(struct USART *config, uint8_t *msg, uint32_t len);
void USART_Attach_Receive_Interrupt(struct USART *config, void (*function) (uint8_t), uint8_t priority);


#endif // USART_H
