#include "stm32f10x.h"
#include "controle_voilier.h"


int main(void){
	init_moteur();
	set_motor(1, 75);
	start_moteur();
//	stop_moteur();
}
	