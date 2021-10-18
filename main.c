#include "stm32f10x.h"
#include "controle_servo_moteur.h"


int main(void){
	init_servo_moteur();
	set_servo_motor(90);
	start_servo_moteur();

	while(1);
}
