#include <reg51.h>
#include "ADC0808.h"
#include "7Seg4Dig_Anode.h"



sbit led = P3^7;

uchar rxData;



void setup_UART()
{
	TMOD = 0x20;	// enable timer1, auto reload
	TH1 = -3;	 	// 9600	Baud rate
	SCON = 0x50; 	// 8 bit uart, 1 stopbit, REN enabled
	TR1 = 1;  		// start timer1
	IE = 0x90;		// enable global, serial port interrupt												
}



void serial_int(void) interrupt	4	 	// turn on/off led
{	
	if (RI)
	{		
		rxData = SBUF;	
		RI = 0;		
		switch(rxData)
		{
			case('0'):	{led=0; break;}
			case('1'):	{led=1; break;}	
		}			
	}	
}



void transmitData(uchar Data)
{
 	SBUF = Data;
	while (TI == 0);
	TI = 0;
}



void main()
{
	uchar hundreds, dozens, units, channel, i;

	setup_UART();

	for (channel = 0; channel < 8; channel++)
	{ 
		for (i = 0; i < 30; i++)
		{
			Led7Seg_scan = led7seg_dig1;
			Led7Seg_data = dig[channel+1];
			on_DP;
			delayScan(500);

			ADC0808_read(channel);

			hundreds = ADC0808_DATA / 100;
			dozens = (ADC0808_DATA / 10) % 10;
			units = ADC0808_DATA % 10;
				   
			Led7Seg_scan = led7seg_dig2;
			Led7Seg_data = dig[hundreds];
			delayScan(500);

			Led7Seg_scan = led7seg_dig3;
			Led7Seg_data = dig[dozens];
			delayScan(500);

			Led7Seg_scan = led7seg_dig4;
			Led7Seg_data = dig[units];
			delayScan(500);				
		}

		transmitData(ADC0808_DATA);
	}
}
