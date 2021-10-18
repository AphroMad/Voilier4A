#include "MyGPIO.h"

	//GPIOC->CRH = (GPIOC->CRH & 0xFFFFF0FF) | OUTPUT_PUSHPULL << 8;
	//GPIOC->CRH = (GPIOC->CRH & 0xFFFFFFF0) | INPUT_FLOATING;
	

void MyGPIO_Init  (MyGPIO_Struct_TypeDef * GPIOStructPtr) {
	// Activation du port
	switch((int)GPIOStructPtr->GPIO){
		case (int)GPIOA : 
			RCC->APB2ENR |= (0x01 << 2); 
			break ;
		case (int)GPIOB : 
			RCC->APB2ENR |= (0x01 << 3); 
			break ;
		case (int)GPIOC : 
			RCC->APB2ENR |= (0x01 << 4); 
			break ;
		case (int)GPIOD : 
			RCC->APB2ENR |= (0x01 << 5); 
			break ;
		case (int)GPIOE : 
			RCC->APB2ENR |= (0x01 << 6); 
			break ;
		case (int)GPIOF : 
			RCC->APB2ENR |= (0x01 << 7); 
			break ;
		case (int)GPIOG : 
			RCC->APB2ENR |= (0x01 << 8); 
			break ;
	}
	
	if(GPIOStructPtr->GPIO_Pin>7 ){ // CRH 
		unsigned int offset = (GPIOStructPtr->GPIO_Pin-8)*4 ;
		GPIOStructPtr->GPIO->CRH = (GPIOStructPtr->GPIO->CRH & ~(0x0000000F << offset)) | GPIOStructPtr->GPIO_Conf << offset; 
	} else { // CRL 
		unsigned int offset = (GPIOStructPtr->GPIO_Pin)*4 ; 
		GPIOStructPtr->GPIO->CRL = (GPIOStructPtr->GPIO->CRL & ~(0x0000000F << offset)) | GPIOStructPtr->GPIO_Conf << offset;
	}
	
	
}

int  MyGPIO_Read  (GPIO_TypeDef * GPIO, unsigned char GPIO_Pin) {
	return ((GPIO->IDR & 0x0001 << GPIO_Pin) == 0x0001 << GPIO_Pin);
}

int  MyGPIO_Write  (GPIO_TypeDef * GPIO, unsigned char GPIO_Pin, unsigned char value) {
	return (GPIO->BSRR = (0x00010000 << GPIO_Pin) | (value << GPIO_Pin));
}


void MyGPIO_Set   (GPIO_TypeDef * GPIO, unsigned char GPIO_Pin) {
	GPIO->BSRR = (0x00000001 << GPIO_Pin);
}

void MyGPIO_Reset (GPIO_TypeDef * GPIO, unsigned char GPIO_Pin) {
	GPIO->BSRR = (0x00010000 << GPIO_Pin);
}
void MyGPIO_Toggle(GPIO_TypeDef * GPIO, unsigned char GPIO_Pin) {
	GPIO->ODR ^= (0x1 << GPIO_Pin);
}
