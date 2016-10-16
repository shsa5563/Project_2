/*
 * circular_buffer_test.h
 *
 *  Created on: Oct 10, 2016
 *      Author: Satyanarayana
 */

#ifndef SOURCES_CIRCULAR_BUFFER_TEST_H_
#define SOURCES_CIRCULAR_BUFFER_TEST_H_

void initialize_test(void);
void buff_full_test(void);
void buff_empty_test(void);
void put_item_tobuffer_test(uint8_t itemtoadd);
void read_delete_item_frombuffer_test(void);
circular_buff_t circ_buff1;

#endif /* SOURCES_CIRCULAR_BUFFER_TEST_H_ */
