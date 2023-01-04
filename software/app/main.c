#include <stdio.h>
#include <unistd.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"


int main(){
	int button_value;
	int pio_adr_led = 0x01;
	int switch_value;
	int time;
	
	while(1){
		/*GESTION DE LA VITESSE CHENILLARD*/
		switch_value = IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE);
		if (switch_value == 0){
			time = 25000;
		}
		else{
			time = switch_value * 10000;
		}
		
		/*CHENILLARD*/
		button_value = IORD_ALTERA_AVALON_PIO_DATA(PUSH_BUTTONS_BASE);
		if (button_value == 3){
			IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE,0);
		}
		else if(button_value == 1){
			for (int i = 0; i<9; i++){
				IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE,pio_adr_led);
				pio_adr_led = pio_adr_led << 1;
				usleep(time);
			}
			
			for (int i = 0; i<9; i++){
				IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE,pio_adr_led);
				pio_adr_led = pio_adr_led >> 1;
				usleep(time);
			}
		}
	}
  return 0;
}
