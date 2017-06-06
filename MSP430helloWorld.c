#include "msp430g2553.h"

unsigned int i;

void delay(){
i = 50000;
	while(i>0)
		i--;
}

void main(void){
	WDTCTL = WDTPW + WDTHOLD; 	// stop watchdog timer
	P1DIR |= 0x01;			// set P1.0 as output

	while(1){
		P1OUT ^= 0x01;		// toggle P1.0 using XOR
		delay(); 
	}
}
