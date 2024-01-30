/*
 * baselib.h
 *
 *  Created on: Jan 17, 2024
 *      Author: MKS
 */

#ifndef SRCCPP_COMMON_BASELIB_H_
#define SRCCPP_COMMON_BASELIB_H_
#include "main.h"
#include <string.h>

#define Readbit(v,p) (v & (1<<p))

uint8_t clearbit(uint8_t v,uint8_t p);
uint8_t setbitAC(uint8_t v,uint8_t p);
inline uint8_t clearbit(uint8_t v,uint8_t p)
{
return (v & ~(1<<p));
}
inline uint8_t setbitAC(uint8_t v,uint8_t p)
{
return (v | (1<<p));
}

#define highByte(a) (((a) >> 8) & 0xFF)
#define lowByte(a) ((a) & 0xFF)

int get_index(char* array,char c)
{
	char *i = strchr(array,c);
	if(i == NULL)
	{
		return -1;
	}
	return (int)(i-array);
}

#endif /* SRCCPP_COMMON_BASELIB_H_ */
