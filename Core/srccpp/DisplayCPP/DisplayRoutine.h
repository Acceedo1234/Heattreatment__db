/*
 * DisplayRoutine.h
 *
 *  Created on: 01-Feb-2023
 *      Author: MKS
 */

#ifndef SRCCPP_DISPLAYCPP_DISPLAYROUTINE_H_
#define SRCCPP_DISPLAYCPP_DISPLAYROUTINE_H_
#include "GLCD.h"


class DisplayRoutine {
public:
	DisplayRoutine();
	virtual ~DisplayRoutine();
	void run();
	void Init();

private:
	GLCD m_gLCDDrive;
	unsigned char Lpdc[15]="    HTF-03  ";
	unsigned char Prod[14]="Process:";
	unsigned char colon[2]=":";
	unsigned char space[7]="      ";
	unsigned char backslash[2]="/";
	unsigned char production[10]=" Temp1 :";
	unsigned char rejection[10] =" Temp2 :";
	unsigned char Mrejection[13]="Timer 1:";
	unsigned char Mtimer[13]="Timer 2:";
	unsigned char Wifi[12]="  WI-FI :";
	void value2Digit(uint8_t value,uint8_t posLine,uint8_t posCol);
	void value4Digit(uint16_t value4dig,uint8_t posLine,uint8_t posCol);
	uint8_t GLCDNumericArray[2];
	uint8_t gLCDNumericArraySize_4[4];

};

#endif /* SRCCPP_DISPLAYCPP_DISPLAYROUTINE_H_ */
