// Toggling LED using switch-interrupt flag

#include"msp430g2234.h"

void configureClock(){
	// set system DCO to 8MHz
	BCSCTL1 = CALB1_8MHZ;
	DCOCTL = CALDCO_8MHZ;

	// set LFXT1 to the VLO @ 12 KHz
	BCSCTL3 |= LFXT1S_2;
}

void main(){
	WDTCTL = WDTPW + WDTHOLD;	// stop watchdog timer
	configureClock();

	// configure LED on P1.0
	P1DIR = BIT0;			// P1.0 is output
	P1OUT &= ~BIT0;

	// configure switch on P1.2
	P1REN |= BIT2;			// P1.2 enable pullup/pulldown
	P1OUT = BIT2;			// P1.2 pullup
	P1IES |= BIT2;			// P1.2 Hi/Lo edge
	P1IFG &= ~BIT2;			// P1.2 IFG cleared

	while(1){
		if(P1IFG & BIT2){	// P1.2 IFG cleared
			P1IFG &= ~BIT2;
			P1OUT ^= BIT0;			
		}
	}
}
