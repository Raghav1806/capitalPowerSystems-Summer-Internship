// Toggle LED using switch-low power mode

/* 
After setting up the LED and switch we go to LPM4, where
energy is greatly conserved. The MSP430 waits for the interrupt. Once the switch is pressed, the LED is toggled and we exit LPM4.
*/ 

#include "msp430g2234.h"

void configureClock(){
	BCSCTL1 = CALBC1_8MHZ;
	DCOCTL = CALDCO_8MHZ;

	BCSCTL3 |= LFXT1S_2;
}

void main(void){
	WDTCTL = WDTPW + WDTHOLD;	// stop watchdog timer
	configureClock();

	// configure LED on P1.0
	P1DIR = BIT0;			// P1.0 output
	P1OUT &= ~BIT0;			// P1.0 output set LOW

	// configure switch on P1.2
	P1REN |= BIT2;			// P1.2 enable pullup/pulldown
	P1OUT = BIT2;			// P1.2 pullup
	P1IE |= BIT2;			// P1.2 interrupt enabled
	P1IES |= BIT2;			// P1.2 Hi/Lo falling edge
	P1IFG &= ~BIT2;			// P1.2 IFG cleared

	// Enter low power mode 4 (after enabling interrupt)
	__bis_SR_register(LPM4_bits + GIE);

	// interrupt ran and we lwft LPM4, we end up here
	while(1){
		// Execute some important code
	}
}

// Port 1 interrupt service routine
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void){
	P1OUT ^= BIT0;			// Toggle LED
	P1IFG &= ~BIT2;			// P1.2 IFG cleared
	__bic_SR_register_on_exit(LPM4_bits)	// exit LPM (if needed)
}
