#include "msp430g2253.h"

void configureClock(){
	// set system DCO to 8MHz
	BCSCTL1 = CALBC1_8MHz;
	DCOCTL = CALDCO_8MHz;

	// set LFXT1 to the VLO @ 12KHz
	BCSCTL3 |= LFXT1S_2;
}

void delay(){
unsigned int x;
x = 50000;
	while(x > 0){
		x--;
	}
}

void main(void){
WDTCTL = WDTPW + WDTHOLD;
configureClock();

P1DIR |= 0x01;
	while(1){
		P1OUT ^= 0x01;
		delay();
	}
}
