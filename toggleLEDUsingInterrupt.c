// Toggling an LED using concept of interrupt
#include "msp430g2254.h"

void configureClock(){
	BCSCTL1 = CALBC1_8MHZ;
	DCOCTL = CALDCO_8MHZ;

	BCSCTL3 |= LFXT1S_2;
}

void main(){
	WDTCTL = WDTPW + WDTHOLD;	// stop watchdog timer

	// configure LED on P1.0
	P1DIR = BIT0;			// P1.0 output
	P1OUT &= ~BIT0;			// LED is initially OFF

	// configure switch on P1.2
	P1REN |= BIT2;			// P1.2 enable pullup/pulldown
	P1OUT = BIT2;			// P1.2 pullup
	P1IE |= BIT2;			// P1.2 interrupt enabled
	P1IES |= BIT2;			// P1.2 Hi/Lo falling edge
	P1IFG &= ~BIT2;			// P1.2 IFG cleared

	_EINT();

	while(1){
		// Execute some other code
	}
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
	P1OUT ^= BIT0;			// toggle LED at P1.0
	P1IFG &= ~BIT2;			// P1.2 IFG cleared
}
