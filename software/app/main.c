#include <stdio.h>
#include <unistd.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"

//VERSION POLLING
/*int main(){
	int button_value;
	int pio_adr_led = 0x01;
	int switch_value;
	int time;
	
	while(1){
		//GESTION DE LA VITESSE CHENILLARD
		switch_value = IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE);
		if (switch_value == 0){
			time = 25000;
		}
		else{
			time = switch_value * 10000;
		}
		
		//CHENILLARD
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
}*/

volatile int time = 25000;

//VERSION INTERRUPTION
static void irqhandler_push_button(void* context){
	int pio_adr_led = 0x01;
	for (int i = 0; i<9; i++){
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE,pio_adr_led);
		pio_adr_led = pio_adr_led << 1;
		usleep(time);
	}
			
	for (int i = 0; i<10; i++){
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE,pio_adr_led);
		pio_adr_led = pio_adr_led >> 1;
		usleep(time);
	}
	
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE,0);
	//RESET INTERRUPTION
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PUSH_BUTTONS_BASE, 0b1);
}

static void irqhandler_switches(void* context){
	int switch_value;
	//GESTION DE LA VITESSE CHENILLARD
	//alt_printf("HELLO");
	switch_value = IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE);
	if (switch_value == 0){
		time = 25000;
	}
	else{
		time = switch_value * 10000;
	}
	//RESET INTERRUPTION
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCHES_BASE, 0xf);
}

int main(){
	//ENABLE INTERRUPTION PUSH_BUTTON
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PUSH_BUTTONS_BASE, 0b1);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PUSH_BUTTONS_BASE, 0b1);
	alt_ic_isr_register(PUSH_BUTTONS_IRQ_INTERRUPT_CONTROLLER_ID,PUSH_BUTTONS_IRQ, (void*)irqhandler_push_button, NULL, 0);
	//ENABLE INTERRUPTION SWITCHES
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(SWITCHES_BASE, 0xf);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCHES_BASE, 0xf);
	alt_ic_isr_register(SWITCHES_IRQ_INTERRUPT_CONTROLLER_ID,SWITCHES_IRQ, (void*)irqhandler_switches, NULL, 0);
	while(1){
	}
	return 0;
}