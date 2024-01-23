/*
 * DisplayRoutine.cpp
 *
 *  Created on: 01-Feb-2023
 *      Author: MKS
 */

#include "DisplayRoutine.h"
//#include <sstream.h>
uint8_t GLCDRefreshFlag;

extern uint8_t wifi_command;
extern uint8_t hour_t,min_t,sec_t;
extern uint8_t Wdate_Rtc,date_Rtc,month_Rtc,year_Rtc;
extern uint16_t MAC_Gen_Prod_Input1_Production,Production_Zeit;
extern uint16_t MAC_Gen_Rej_Input_Production,Rejection_Zeit;
extern uint16_t Manual_RejectionCount;
extern uint16_t SectorPos;

DisplayRoutine::DisplayRoutine() {
	// TODO Auto-generated constructor stub

}

DisplayRoutine::~DisplayRoutine() {
	// TODO Auto-generated destructor stub
}

void DisplayRoutine::run()
{
	//m_gLCDDrive.m_clrlcd();/*  Try in local if not need comment out*/
	m_gLCDDrive.m_lcdputs1(0,1,Lpdc);

//	value2Digit(hour_t,2,0);
//	m_gLCDDrive.m_lcdputs1(15,2,colon);
//	value2Digit(min_t,2,20);
//	m_gLCDDrive.m_lcdputs1(35,2,colon);
//	value2Digit(sec_t,2,40);
//	m_gLCDDrive.m_lcdputs1(54,2,space);
//	value2Digit(date_Rtc,2,65);
//	m_gLCDDrive.m_lcdputs1(81,2,backslash);
//	value2Digit(month_Rtc,2,86);
//	m_gLCDDrive.m_lcdputs1(103,2,backslash);
//	value2Digit(year_Rtc,2,110);
	m_gLCDDrive.m_lcdputs1(0,2,Prod);
	value4Digit(MAC_Gen_Prod_Input1_Production,2,66);
	m_gLCDDrive.m_lcdputs1(98,2,space);

	m_gLCDDrive.m_lcdputs1(0,3,production);
	value4Digit(MAC_Gen_Prod_Input1_Production,3,66);
	m_gLCDDrive.m_lcdputs1(98,3,space);

	m_gLCDDrive.m_lcdputs1(0,4,rejection);
	value4Digit(MAC_Gen_Rej_Input_Production,4,66);
	m_gLCDDrive.m_lcdputs1(98,4,space);

	m_gLCDDrive.m_lcdputs1(0,5,Mrejection);
	value4Digit(Manual_RejectionCount,5,66);
	m_gLCDDrive.m_lcdputs1(98,5,space);

	m_gLCDDrive.m_lcdputs1(0,6,Mtimer);
	value4Digit(Manual_RejectionCount,6,66);
	m_gLCDDrive.m_lcdputs1(98,6,space);

	m_gLCDDrive.m_lcdputs1(0,7,Wifi);
	value4Digit(wifi_command,7,66);
	m_gLCDDrive.m_lcdputs1(98,7,space);
//	value2Digit(SectorPos,6,95);
	//Prod

}

void DisplayRoutine::value2Digit(uint8_t value,uint8_t posLine,uint8_t posCol)
{
	GLCDNumericArray[0] =(unsigned int)(((value%100)/10)+0x30);
    GLCDNumericArray[1] =(unsigned int)((value%10)+0x30);
	m_gLCDDrive.m_lcdputs1(posCol,posLine,GLCDNumericArray);
}
void DisplayRoutine::value4Digit(uint16_t value4dig,uint8_t posLine,uint8_t posCol)
{
	gLCDNumericArraySize_4[0] =(unsigned char)(((value4dig%10000)/1000)+0x30);
	gLCDNumericArraySize_4[1] =(unsigned char)((value4dig%1000)/100+0x30);
	gLCDNumericArraySize_4[2] =(unsigned char)(((value4dig%100)/10)+0x30);
	gLCDNumericArraySize_4[3] =(unsigned char)((value4dig%10)+0x30);
	m_gLCDDrive.m_lcdputs1(posCol,posLine,gLCDNumericArraySize_4);
}

void DisplayRoutine::Init()
{
	m_gLCDDrive.m_displayon();
	m_gLCDDrive.m_setstartline(0);
	m_gLCDDrive.m_clrlcd();


}

