#include "controle_servo_moteur.h"
#include "stm32f10x.h"
#include "MyGPIO.h"

// Definir les GPIO que l'on va utiliser 
MyGPIO_Struct_TypeDef GPIO_servo_moteur;
MyTimer_Struct_TypeDef TIM3_CH3;


/* initialiser les GPIO correspondant au moteur */
void init_servo_moteur(void){
	GPIO_servo_moteur.GPIO = GPIOB;
	GPIO_servo_moteur.GPIO_Pin = 0;
	GPIO_servo_moteur.GPIO_Conf = AltOut_Ppull;
	
	TIM3_CH3.Timer=TIM3;
	TIM3_CH3.ARR= 14400;
	TIM3_CH3.PSC= 100;
	
	MyGPIO_Init(&GPIO_servo_moteur);
	MyTimer_Base_Init(&TIM3_CH3);
	MyTimer_PWM(TIM3, 3);
}
	
void set_servo_motor(int angle){
	// Définir la vitesse
	// CNT 0->320
	TIM3->CCR3=3.2*(5+(angle/36));
}

void start_servo_moteur(void){
	MyTimer_Base_Start(TIM3_CH3);
}

void stop_servo_moteur(void) {
	MyTimer_Base_Stop(TIM3_CH3);
}
