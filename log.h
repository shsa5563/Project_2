/*
 * log.h
 *
 *  Created on: Oct 10, 2016
 *      Author: Satyanarayana
 */

#ifndef SOURCES_LOG_H_
#define SOURCES_LOG_H_

void LOG_0(uint8_t * data, uint32_t len);
void LOG_1(uint8_t * data, float param,uint32_t point);
void reverse(uint8_t *str, uint32_t len);
uint32_t intToStr(uint32_t val_data, uint8_t str[], uint32_t len);
uint8_t ftoa(float _float_val, uint8_t *res, uint32_t afterdecimal);

#endif /* SOURCES_LOG_H_ */
