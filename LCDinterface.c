#include "msp430g2253.h"

#define LCDMEMS 11		// LCD memories used (3-13)
// pointer to LCD memory used, allows use of array LCDMem[]
uint8_t *const LCDMem = (uint8_t *)&LCDM3;

void InitLCD(void){
	int i;
	for(i = 0; i < LCDMEMS; i++)	// clear LCD memory used
		LCDMem[i] = 0;
	P5SEL = BIT4 | BIT3 | BIT2;	// select COM[3:1] function
	LCDAPCTL0 = LCDS4|LCDS8|LCDS12|LCDS16|LCDS20|LCDS24;
					// enable LCD segs 4-27
	LCDAVCTL0 = 0;			// no charge pump, everything internal
	LCDACTL = LCDFREQ_128 | LCD4MUX | LCDSON | LCDON;
					// ACLK/128, 4mux, segments on, LCD_A on
}

void main(void){
	int i, j;
	enum(up, down) direction;					// direction of johnson counter

	WDTCTL = WDTPW|WDTHOLD;						// stop watchdog timer
	P2OUT = BIT2;
	P2DIR = BIT1|BIT2;						// set LEDs to output
	InitLCD();							// initialize SBLCDA4
	TACCR0 = 0X1000;						// upper limit of count for TAR
	TACCTL0 = CCIE;							// enable compare 0 interrupts
	TACTL = MC_1|TASSEL_1|TACLR;					// set up and start timerA
	direction = up;							// start johnson counter up
	while(1){
		for(i = 0; i < LCDMEMS; i++){				// count through LCD memories
			for(j = 0; j < 8; j++){				// count through bits
				__low_power_mode_3();
									// shift left, insert 1 on right	
				if(direction == up)
					LCDMem[i] = (LCDMem[i] << 1) | BIT0;
									// shift left, insert 0 (default)
				else
					LCDMem[i] = (LCDMem[i] << 1)
			}	
		__low_power_mode_3();					// extra delays after each character
		__low_power_mode_3();
			
		}
	if(direction == up) 
		direction = down;
	else
		direction = up;
	}
}

									// ISR for Timer A channel 0
#pragma vector = TIMERA0_VECTOR
__interrupt void TIMERA0_ISR(void){
	P2OUT ^= BIT1|BIT2; 						// toggle LEDs
	__low_power_mode_off_on_exit();					// restore active mode on return
}
