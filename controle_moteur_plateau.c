#include "controle_moteur_plateau.h"

// Definir les GPIO que l'on va utiliser 
MyGPIO_Struct_TypeDef GPIO_orient_moteur;
MyGPIO_Struct_TypeDef GPIO_vitesse_moteur;
MyTimer_Struct_TypeDef TIM2_CH2;


/* initialiser les GPIO correspondant au moteur */
void init_moteur(void){
	GPIO_orient_moteur.GPIO = GPIOA;
	GPIO_orient_moteur.GPIO_Pin = 5;
	GPIO_orient_moteur.GPIO_Conf = Out_Ppull;
	
	GPIO_vitesse_moteur.GPIO = GPIOA;
	GPIO_vitesse_moteur.GPIO_Pin = 1;
	GPIO_vitesse_moteur.GPIO_Conf = AltOut_Ppull;
	
	TIM2_CH2.Timer=TIM2;
	TIM2_CH2.ARR= 320;
	TIM2_CH2.PSC= 11;
	
	MyGPIO_Init(&GPIO_orient_moteur);
  MyGPIO_Init(&GPIO_vitesse_moteur);
	MyTimer_Base_Init(&TIM2_CH2);
	MyTimer_PWM(TIM2, 2);
}
	
void set_motor(int orientation, int vitesse){
	// Definir l'orientation
	if (orientation==1){
		MyGPIO_Set(GPIO_orient_moteur.GPIO, GPIO_orient_moteur.GPIO_Pin);
	} else {
		MyGPIO_Reset(GPIO_orient_moteur.GPIO, GPIO_orient_moteur.GPIO_Pin);
	}
	
	// D�finir la vitesse
	// CNT 0->500
	TIM2->CCR2=3.2*vitesse; 
}

void start_moteur(void){
	MyTimer_Base_Start(TIM2_CH2);
}

void stop_moteur(void) {
	MyTimer_Base_Stop(TIM2_CH2);
}
