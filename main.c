/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL25Z4.h"
#include "circbuff.h"
#include "led.h"
#include "uart.h"
#include "circular_buffer_test.h"
#include "log.h"
#define test_function 1
int main(void)
{
	UART0_init();//supporting the baud rate of 57600
    Initialize_LED();
    uint32_t i=0;
    uint8_t transmit_str[500]="\n\rEnter 't' for echo mode - press enter after entering the string:\n\rTo Play with the LED press a,d - to change color ; d,w - to change the intensity\n\r",recieve_str[100]="0";

	   //test function
#ifndef test_function
		    void initialize_test(void);
		    void buff_full_test(void);
		    void buff_empty_test(void);
		    void put_item_tobuffer_test(uint8_t itemtoadd);
		    void read_delete_item_frombuffer_test(void);
#endif

//log function with compile time switch
#ifndef Log_function

		  	char string1[]="Testing123 Testing123, Serial Print Test, no params";
		    char string2[]="	This is an integer number:";
		    char string5[]="	This is a floating point number:";
		    float var2=200;
		    float var3=4096;
		    float var4=123456;
		    float var5=1543.321;

	#ifdef _FRDM   //FRDM UART
	    LOG_0(string1,40);
	    LOG_1(string2,var2,0);
	    LOG_1(string2,var3,0);
	    LOG_1(string2,var4,0);
	    LOG_1(string5,var5,3);
	#endif

	#ifdef _BBB   //BBB PRINTF

	    LOG_0(string1,40);
	    LOG_1(string2,var2,0);
	    LOG_1(string2,var3,0);
	    LOG_1(string2,var4,0);
	    LOG_1(string5,var5,3);
	#endif
#endif

#ifdef _FRDM   //BBB PRINTF
	    put_data_with_Interrupt(transmit_str);
#endif

#ifdef _BBB   //BBB PRINTF
	    printf("%s",transmit_str);
#endif

	while(1)
	{
		uint8_t input,cond_check;
#ifdef _FRDM
		buffer_status ec=buff_empty(&_recieve_buffer);

		if(ec==buffer_not_empty )
		{
	     input=read_delete_item_frombuffer(&_recieve_buffer);
#endif

#ifdef _BBB   //BBB PRINTF
	     scan(&input);
#endif
			if(input=='t' || input==0xd)
			{
				cond_check=input;

			}

			if(cond_check=='t')
			{
				recieve_str[i] = input;
				i++;
			}
		    else if(cond_check==0xd)
			{
		    	cond_check=0;
			    i=0;
#ifdef _FRDM
			    put_data_with_Interrupt(&recieve_str[1]);
#endif

#ifdef _BBB
			    for(int i =1; i<MAX_LEN; i++)
			   	{
			   	   printf("%s",recieve_str[i]);
			   	}
#endif
			}
		    else if((input=='a'|| input=='s' || input=='w' || input=='d'))
		    {
		    	Change_LEDColor(input);

		    }
		}
#ifdef _FRDM
	}
#endif
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
