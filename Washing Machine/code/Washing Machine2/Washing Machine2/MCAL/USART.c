/*
 * USART.c
 *
 * Created: 8/20/2019 2:53:52 PM
 *  Author: shaher
 */ 

#include "USART.h"

void  USART_Init(uint16 Baud_Rate, Bits_Set Bit, USART_Mode Mode,INT_Enable INT,Parity_Mode Parity,Stop_Bits Stop)
{
	uint16 _UBRR;
	if (Mode != USART_Async)
	{
		_UBRR=(uint16)((((double)F_CPU) / (2.0*Baud_Rate))-1.0);
	}
	else
	{
		if(Double_Speed)
			_UBRR=(uint16)((((double)F_CPU) / (8.0*Baud_Rate))-1.0);
		else		
			_UBRR=(uint16)((((double)F_CPU) / (16.0*Baud_Rate))-1.0);
	}
	UBRR(_UBRR);
	
	
	UCSRA =(Double_Speed<<U2X)|(Mulit_processor<<MPCM);
	UCSRB =INT|(1<<RXEN)|(1<<TXEN)|(_9thBit<<UCSZ2);
	UCSRC =(1<<URSEL)|(Mode)|(Bit)|(Parity)|(Stop<<3);
}
void  USART_SendByte(uint8 Data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	
	#if _9thBit
	/* Copy 9th bit to TXB8 */
	UCSRB &= ~(1<<TXB8);
	if ( Data & 0x0100 )
	UCSRB |= (1<<TXB8);
       #endif
	
	/* Put data into buffer, sends the data */
	UDR = Data;

}
uint8 USART_RecByte(void)
{
	#if _9thBit
    unsigned char status, resh, resl;
    /* Wait for data to be received */
    while ( !(UCSRA & (1<<RXC)) )
    ;
    /* Get status and 9th bit, then data */
    /* from buffer */
    status = UCSRA;
    resh = UCSRB;
    resl = UDR;
    /* If error, return -1 */
    if ( status & (1<<FE)|(1<<DOR)|(1<<PE) )
    return -1;
    /* Filter the 9th bit, then return */
    resh = (resh >> 1) & 0x01;
    return ((resh << 8) | resl);
    #else
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) );
	/* Get and return received data from buffer */
	return UDR;
	#endif
}