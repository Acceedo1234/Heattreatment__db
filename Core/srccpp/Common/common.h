/*
 * common.h
 *
 *  Created on: Dec 19, 2022
 *      Author: MKS
 */

#ifndef SRCCPP_COMMON_COMMON_H_
#define SRCCPP_COMMON_COMMON_H_
#include "main.h"
#define true 1

class common {
public:
	common();
	virtual ~common();
	GPIO_PinState ReadtheValueAssignPinstate(uint8_t position, uint8_t value)
	{
		GPIO_PinState pinstate;
		position = 1 << position;
		if(position & value){
			pinstate = GPIO_PIN_SET;
		}
		else
		{
			pinstate = GPIO_PIN_RESET;
		}
		return(pinstate);
	}
};

#endif /* SRCCPP_COMMON_COMMON_H_ */
