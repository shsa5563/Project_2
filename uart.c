/*
 * uart.c
 *
 *  Created on: 07-Oct-2016
 *      Author: Satyanarayana
 */
#include "MKL25Z4.h"
#include "uart.h"
#include "circbuff.h"
//send char to RealTerm through UART
void send_char(char _value)
    {
        while(!(UART0->S1 & 0xC0));
          UART0->D =_value;

    }
//send string to RealTerm using UART
void send_string(char s[])
{
        int i=0;

        while (s[i] != '\0')
        {
            send_char(s[i]);
            i++;
        }
#ifdef _FRDM
	    send_char('\n');
	    send_char('\r');
#endif
#ifdef _BBB
	    printf("\n\n");
#endif
}
void UART0_init(void)
{
	__disable_irq();
		SIM->SCGC4 |= 0x0400;
		SIM->SOPT2 |= 0x04000000;

		UART0->C2 = 0;
		UART0->BDH = 0x00;
		UART0->BDL = 0x17;
		UART0->C4 = 0x0F;
		UART0->C1 = 0x00;
		UART0->C2 = 0x08|0x24;

		SIM->SCGC5 = 0x0200;
		PORTA->PCR[2]= 0x0200;
		PORTA->PCR[1]= 0x0200;
		_transmit_buffer.buff = allocate_memory(&_transmit_buffer);
			_transmit_buffer.head=_transmit_buffer.buff;
					 	_transmit_buffer.tail=_transmit_buffer.buff;
					 	_transmit_buffer.buff=_transmit_buffer.buff;
					 	_transmit_buffer.num_items= 0;
					 	_transmit_buffer.length = MAX_LEN;
		    _recieve_buffer.buff = allocate_memory(&_recieve_buffer);
		    _recieve_buffer.head=_recieve_buffer.buff;
					_recieve_buffer.tail=_recieve_buffer.buff;
					_recieve_buffer.buff=_recieve_buffer.buff;
					_recieve_buffer.num_items= 0;
					_recieve_buffer.length = MAX_LEN;
NVIC->ISER[0] |= 0x00001000;
NVIC_SetPriority(UART0_IRQn,2);
__enable_irq();
}

//Extra Credit: Circular Buffer Implementation with Transmission Interrupts
void put_data_with_Interrupt(uint8_t *_value)
{
	uint32_t i=0;
	while(*(_value+i) !='\0')
	{
	put_item_tobuffer(&_transmit_buffer,*(_value+i));
	i++;
	}
	UART0_C2 |= UART0_C2_TIE_MASK;
}

uint8_t data=0;
//UART handler
void UART0_IRQHandler()
{
buffer_status _bufferstatus = buff_full(&_recieve_buffer);
if((UART0_S1 & (UART0_S1_RDRF_MASK)) && _bufferstatus==buffer_not_full)
{
	uint8_t mode;
	uint32_t i;
	data= UART0->D;
	put_item_tobuffer(&_recieve_buffer,data);
}

else if(_bufferstatus==buffer_empty)
	{
		UART0_C2 &= ~UART0_C2_RIE_MASK;
	}

	 _bufferstatus = buff_empty(&_transmit_buffer);
	if((UART0_S1 & (UART0_S1_TDRE_MASK))&& _bufferstatus==buffer_not_empty)
	{

		UART0_D =  read_delete_item_frombuffer(&_transmit_buffer);
	}
	else if(_bufferstatus==buffer_empty)
	{
		UART0_C2 &= ~UART0_C2_TIE_MASK;
	}

}

