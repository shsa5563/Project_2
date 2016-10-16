/*
 * circular_buffer_test.c
 *
 *  Created on: Oct 10, 2016
 *      Author: Satyanarayana
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "MKL25Z4.h"
#include "uart.h"
#include "circbuff.h"
#include "circular_buffer_test.h"

void initialize_test(void)
{
	char passstring1[50]="circ_buff UNIT TEST: 1/5-<initialize>....PASS\n\r";
	circ_buff1.buff=allocate_memory(&circ_buff1);
	circ_buff1.head=circ_buff1.buff;
	circ_buff1.tail=circ_buff1.buff;
	send_string(passstring1);
}
void put_item_tobuffer_test(uint8_t itemtoadd)
{
	buffer_status _buff_status;
	char passstring4[50]="circ_buff UNIT TEST: 4/5-<add_data>....PASS\n\r";
	char failstring4[50]="circ_buff UNIT TEST: 4/5-<add_data>....FAIL\n\r";
	_buff_status=put_item_tobuffer(&circ_buff1, itemtoadd);

	if(_buff_status==success_item_add)
	{
		send_string(passstring4);
	}
	else if(_buff_status==success_item_add_wraparound_override)
	{
		send_string(passstring4);
	}
	else if(_buff_status==buffer_full)
	{
		send_string(failstring4);
	}
}

void read_delete_item_frombuffer_test(void)
{
	int _buff_status;
	char passstring5[50]="circ_buff UNIT TEST: 5/5-<remove_data>....PASS\n\r";
	char failstring5[50]="circ_buff UNIT TEST: 5/5-<remove_data>....FAIL\n\r";
	_buff_status=read_delete_item_frombuffer(&circ_buff1);

	if(_buff_status!=-1)
	{
		send_string(passstring5);
	}
	else if(_buff_status==-1)
	{
		send_string(failstring5);
	}
}

void buff_full_test(void)
{
	buffer_status  _buff_status;
	char passstring2[50]="circ_buff UNIT TEST: 2/5-<initialize>....PASS\n\r";
	char failstring2[50]="circ_buff UNIT TEST: 2/5-<initialize>....FAIL\n\r";
	_buff_status=buff_full(&circ_buff1);

	if(_buff_status==buffer_full)
	{
		send_string(passstring2);
	}
	else if(_buff_status==buffer_not_full)
	{
		send_string(failstring2);
	}
}

void buff_empty_test(void)
{
	buffer_status  _buff_status;
	char passstring3[50]="circ_buff UNIT TEST: 3/5-<buff_empty>....PASS\n\r";
	char failstring3[50]="circ_buff UNIT TEST: 3/5-<buff_empty>....FAIL\n\r";
	_buff_status=buff_empty(&circ_buff1);

	if(_buff_status==buffer_empty)
	{
		send_string(passstring3);
	}
	else if(_buff_status==buffer_not_empty)
	{
		send_string(failstring3);
	}
}

