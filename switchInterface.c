// Program to light LED1 when button B1 is pressed using interrupts and low power mode 4

#include "msp430g2253.h"

void main(void){
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P2OUT_bit.P2OUT_3 = 1;		// preload LED1 off (active low)
	P2DIR_bit.P2DIR_3 = 1;		// Set pin with LED1 to output
	P2IE_bit.P2IE_1 = 1;		// Enable interrupts on edge
	P2IES_bit.P2IES_1 = 1;		// Sensitive to negative edge
	do{
		P2IFG = 0;		// clear any pending interrupts
	}while(P2IFG != 0);

	while(1){
		__low_power_mode_4();	// Low power mode 4
	}
}

// Interrupt service routine for port 2 inputs, device returns to low power mode automatically after ISR
#pragma vector = PORT2_VECTOR
__interrupt void PORT2_ISR(void){
	P2OUT_bit.P2OUT_3 ^= 1;		// toggle LED
	P2IES_bit.P2IES_1 ^= 1;		// toggle edge sensitively

	do{
		P2IFG = 0;		// clear any pending interrupts
	}while(P2IFG != 0);
}
