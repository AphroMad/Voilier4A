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
		.timer.psc = 1,
		.timer.arr = 1000,
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

void usart_receive(uint8_t data) {
	MoteurRotation_Set(&moteur_rotation, 1, data);
}

void setup(void) {
	USART_Init(&usart);
	MoteurRotation_Init(&moteur_rotation);
	Servo_Init(&servo_moteur);
	Encoder_Init(&girouette);
}

void start(void) {
	USART_Start(&usart);
	USART_Attach_Receive_Interrupt(&usart, usart_receive, 8);
	MoteurRotation_Start(&moteur_rotation);
	Servo_Start(&servo_moteur);
	Encoder_Start(&girouette);
}

int main(void) {
	setup();
	start();
	
	MoteurRotation_Set(&moteur_rotation, 1, 50);
	Servo_Set(&servo_moteur, 180);
	while(1) {}
}
