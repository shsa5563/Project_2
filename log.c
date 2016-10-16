/*
 * log.c
 *
 *  Created on: Oct 10, 2016
 *      Author: Satyanarayana
 */


#include "MKL25Z4.h"
#include <stdio.h>
#include "log.h"
#include "uart.h"

uint32_t intToStr(uint32_t val_data, uint8_t str[], uint32_t len)
{
	uint32_t i = 0;
    while (val_data)
    {
        str[i++] = (val_data%10) + '0';
        val_data = val_data/10;
    }
    while (i < len)
        str[i++] = '0';
    reverse(str, i);
    str[i] = '\0';
    return i;
}

uint8_t ftoa(float _float_val, uint8_t *res, uint32_t afterdecimal)
{
    uint32_t ipart = (uint32_t)_float_val;

    // Extract floating part
    float fpart = _float_val - (float)ipart;

    uint32_t i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterdecimal != 0)
    {
        res[i] = '.'; // add dot

    // Get the value of fraction part upto given no.
    fpart = fpart * pow(10, afterdecimal);

    intToStr((int)fpart, res + i + 1, afterdecimal);
    }
}


void LOG_0(uint8_t * data, uint32_t len)
{
#ifdef _FRDM
	send_string(data);
#endif

#ifdef _BBB
    int i;
    for(i=0;i<len;i++)
    {
        printf("%c",data[i]);
    }
#endif
}

void reverse(uint8_t *str, uint32_t len)
{
    uint32_t i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}
void LOG_1(uint8_t * data, float param,uint32_t point)
{
    uint8_t floatchar[50];
    uint8_t *f=floatchar;
    uint32_t length,i=0,j=0,z=0;

    ftoa(param,&floatchar,point);

    for(i=0;data[i]!='\0';++i);
    void LOG_0(uint8_t * data, uint32_t len)
    {
    #ifdef _FRDM
    	send_string(data);
    #endif

    #ifdef _BBB
        int i;
        for(i=0;i<len;i++)
        {
            printf("%c",data[i]);
        }
    #endif
    }    z = i;
    for(j=0;floatchar[j]!='\0';++j,++i)
    {
        data[i]=floatchar[j];
    }

    data[i]='\0';

    for(length=0;data[length]!='\0';length++);
    LOG_0(data,length+1);

    for(j=0;floatchar[j]!='\0';++j,++z)
        {
            data[z]='\0';
        }

}





