/*
 * circbuf.h
 *
 *  Created on: 09-Oct-2016
 *      Author: Satyanarayana
 */

#ifndef SOURCES_CIRCBUF_H_
#define SOURCES_CIRCBUF_H_
#define MAX_LEN 500

typedef enum {
	buffer_full,
	buffer_not_full,
	buffer_empty,
	buffer_not_empty,
	success_item_add,
	success_item_add_wraparound_override,
	error
}  buffer_status;

typedef struct {
	uint8_t *buff;
	uint8_t *head;
	uint8_t *tail;
	uint32_t num_items;
	uint32_t length;
} circular_buff_t;
circular_buff_t _transmit_buffer, _recieve_buffer;

buffer_status buff_full(circular_buff_t *circ_buff);
buffer_status buff_empty(circular_buff_t *circ_buff);
buffer_status put_item_tobuffer(circular_buff_t *circ_buff, uint8_t data);
uint8_t read_delete_item_frombuffer(circular_buff_t *circ_buff);
uint8_t* allocate_memory(circular_buff_t *circ_buff);
void free_buff(circular_buff_t *circ_buff);

#endif /* SOURCES_CIRCBUF_H_ */
