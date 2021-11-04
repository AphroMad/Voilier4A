#include <GPIO.h>
#include <moteur_rotation.h>
#include <servo.h>
#include <encoder.h>
#include <ADC.h>
//#include <I2C.h>
#include <USART.h>

// PA5
// PA1
struct MoteurRotation moteur_rotation = {
	.gpio_orientation.gpio = GPIOA,
	.gpio_orientation.pin = 5,
	.pwm_vitesse = {
		.gpio.gpio = GPIOA,
		.gpio.pin = 1,
		.timer.psc = 0,
		.timer.arr = 1799,
	}
};

// PB0
struct Servo servo_moteur = {
	.pwm = {
		.gpio.gpio = GPIOB,
		.gpio.pin = 0,
		.timer.psc = 100,
		.timer.arr = 14400,
	},
	.min = 0,
	.max = 180,
	.arr_min = 720,
	.arr_max = 1440,
};

// PB6
// PB7
// PA2
struct Encoder girouette = {
	.timer = {
		.timer = TIM4, // PB6, PB7
		.arr = 1440,
	},
	.polarity = ENCODER_POLARITY_FALLING,
	.gpio_reset.gpio = GPIOA,
	.gpio_reset.pin = 2,
};

// PA9
// PA10
struct USART usart = {
	.usart = USART1,
	.word_lenght = USART_WORD_LENGHT_8BITS,
	.parity_control = USART_PARITY_CONTROL_DISABLED,
	.direction = USART_DIRECTION_TX_RX,
	.stop = USART_STOP_1,
	.bauds = 9600,
};

void setup(void) {
	MoteurRotation_Init(&moteur_rotation);
	Servo_Init(&servo_moteur);
	Encoder_Init(&girouette);
	ADC_Init();
	ADC_Pin_Init(ADC_PA4);
	// I2C_Init();
	USART_Init(&usart);
}	

void start(void) {
	MoteurRotation_Start(&moteur_rotation);
	Servo_Start(&servo_moteur);
	Encoder_Start(&girouette);
	USART_Start(&usart);
}

int main(void) {
	setup();
	start();
	while(1) {
	}
}
