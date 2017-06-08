// Using polling, when interrupt occurs (switch is pressed) LED toggles.

#include"msp430g2234.h"

void configureClock(){
	// set system DCO to 8 MHz
	BCSCTL1 = CALBC1_8MHZ;
	DCOCTL = CALDCO_8MHZ;

	// set LFXT1 to the VLO @ 12 KHz
	BCSCTL3 |= LFXTIS_2;
}

unsigned int i;

void delay(){
i = 50000;
	while(i)
		i--;
}

void main(void){
	WDTCTL = WDTPW + WDTHOLD;	// stop watchdog timer
	configureClock();

	// Configure LED on P1.0
	P1DIR = BIT0;			// set P1.0 as output
	P1OUT &= ~BIT0;			// P1.0 as output LOW, LED OFF

	// Configure switch on P1.2
	P1REN |= BIT2;			// Enable pullup/pulldown
	P1OUT = BIT2;			// P1.2 pullup

	while(1){
		if(P1IN & ^BIT2){	// P1.2 is low
			P1OUT ^= BIT0;	// Toggle LED at P1.0
			delay();
		}	
	}
}
