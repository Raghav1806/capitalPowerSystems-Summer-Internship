// ADC sampling of temperature and Vcc

#include "msp430f2254.h"

void main(void){
	WDTCTL = WDTPW + WDTHOLD;	// stop watchdog timer

	// configure MCU clocks
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	// set LFXT1 to the VLO @ 12 KHz
	BCSCTL3 |= LFXTIS_2;

	// configure LED on P1.0
	P1DIR = BIT0;			// P1.0 output
	P1OUT &= ~BIT0;			// P1.0 output set low

/* 
C's volatile keyword is a qualifier that is applied to a variable when it is declared. It tells the compiler that the value of the variable may change at any time--without any action being taken by the code the compiler finds nearby.
*/
 
	volatile long temp;
	int delay, volt;

	// configure ADC to sample temperature sensor
	ADC10CTL1 = INCH_10 + ADC10DIV_4;
	ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON + ADC10IE + ADC10SR;

	for(delay=240; delay>0; delay--);	// delay for allowing reference to settle

	ADC10CTL0 |= ENC + ADC10SC;	// sampling and conversion starts
	__bis_SR_register(CPUOFF + GIE);	// LPM0 with interrupt enabled


	// Read the conversion data
	temp = ADC10MEM;
	ADC10CTL0 &= ~ENC;		// stop ADC conversion

	// Reconfigure ADC to sample Vcc
	ADC10CTL1 = INCH_11;
	ADC10CTL0 = SREF_1 + ADC10SHT_2 + REFON + ADC10ON + ADC10IE + REF2_5V;

	for(delay=240; delay>0; delay--);	// delay for allowing reference to settle
	ADC10CTL0 |= ENC + ADC10SC;		// sampling and conversion start
	__bis_SR_register(CPUOFF + GIE);	// LPM0 with interrupts enabled
	volt = ADC10MEM;
	ADCCTL0 &= ~ENC;
	ADC10CTL0 &= ~(REFON + ADC10ON);	// turn off A/D to save power
}
