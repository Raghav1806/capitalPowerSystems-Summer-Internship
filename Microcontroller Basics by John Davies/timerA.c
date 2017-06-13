#include "masp430g2553.h"

// pins for LEDs
#define LED1	BIT3
#define LED2	BIT4

void main(void){
	WDTCTL = WDTPW|WDTHOLD;	// stop watchdog timer
	P2DIR = LED1|LED2;	// set LED1, LED2 to output
	P2OUT = ~(LED1|LED2);	// set both LEDs to be off initially
	TACTL = MC_2|ID_3|TASSEL_2|TACLR;	// Set up and start Timer A
	// continuous up mode, divide clock by 8, clock from SMCLK, clear timer
	while(1){
		while(TACTL_bit.TAIFG == 0){
			// Wait for overflow, doing nothing
		}
		TACTL_bit.TAIFG = 0;	// clear oveflow flag
		P2OUT ^= LED1|LED2;	// toggle LEDs
	}
}
