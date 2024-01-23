/*
 * Modbus_types.h
 *
 *  Created on: 07-Jan-2023
 *      Author: MKS
 */

#ifndef SRCCPP_MODBUS_MODBUS_TYPES_H_
#define SRCCPP_MODBUS_MODBUS_TYPES_H_

#include "main.h"

struct{
	uint16_t Noofbytesrx;
}read_rxint_set;


uint8_t u8rxbuf[255];

#endif /* SRCCPP_MODBUS_MODBUS_TYPES_H_ */
