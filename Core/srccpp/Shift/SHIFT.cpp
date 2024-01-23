/*
 * SHIFT.cpp
 *
 *  Created on: 15-Feb-2023
 *      Author: MKS
 */
#include "main.h"
#include "SHIFT.h"

extern "C" {
void rtc_get_time(uint8_t *hour,uint8_t *min,uint8_t *sec);
void rtc_get_date(uint8_t *week_day, uint8_t *day,uint8_t *month,uint8_t *year);
void rtc_set_time(uint8_t hour,uint8_t min,uint8_t sec);
void rtc_set_date(uint8_t week_day, uint8_t day,uint8_t month,uint8_t year);
}

uint8_t hour_t,min_t,sec_t;
uint8_t Wdate_Rtc,date_Rtc,month_Rtc,year_Rtc;
uint8_t CurrentShift;
uint8_t UpdateShiftInfo;

extern uint8_t SW_Hour,SW_Minute;
extern uint8_t Updatetimeinfo;
extern uint8_t SW_Date,SW_Month,SW_Year;

SHIFT::SHIFT() {
	// TODO Auto-generated constructor stub

}

SHIFT::~SHIFT() {
	// TODO Auto-generated destructor stub
}

void SHIFT::shiftCalculation(void)
{
	rtc_get_time(&hour_t,&min_t,&sec_t);
	rtc_get_date(&Wdate_Rtc,&date_Rtc,&month_Rtc,&year_Rtc);

	if(Updatetimeinfo)
	{
		Updatetimeinfo=0;
		locTimeTotal    =  (((hour_t)*(60))+(min_t));
		onlineTimeTotal =  (((SW_Hour)*(60))+(SW_Minute));
		if((locTimeTotal <= (onlineTimeTotal-3)) || (locTimeTotal >= (onlineTimeTotal+3)))
		{
			  rtc_set_time(SW_Hour,SW_Minute,30);
		}
		if((date_Rtc != SW_Date) || (month_Rtc != SW_Month) || (year_Rtc != SW_Year))
		{
			rtc_set_date(2,SW_Date,SW_Month,SW_Year);
		}
	}
	TotalMinutesvar = (((hour_t)*(60))+(min_t));
	Shift1_OnTime = (((8)*(60))+(31));	  //495
	Shift1_OffTime = (((16)*(60))+(30)); //974

	Shift2_OnTime = (((16)*(60))+(31));	 //975
	shift2_buffer_time_1 = (((23)*(60))+(59)); // 1439
	Shift2_OffTime = (((0)*(60))+(30));	 //14

	Shift3_OnTime = (((0)*(60))+(31));	//15
	Shift3_OffTime = (((8)*(60))+(30));	 //494

	if((TotalMinutesvar >=  Shift1_OnTime)&&(TotalMinutesvar <= Shift1_OffTime))
	{
	   CurrentShift=1;
	}
	else if(((TotalMinutesvar >=  Shift2_OnTime)&&(TotalMinutesvar <= shift2_buffer_time_1))
				||((TotalMinutesvar>= 0)&&(TotalMinutesvar<=Shift2_OffTime)))
	{//Included one brace to solve warning?
		CurrentShift=2;
	}
	else if((TotalMinutesvar >=  Shift3_OnTime)&&(TotalMinutesvar <= Shift3_OffTime))
	{
		CurrentShift=3;
	}
	else
	{
	/*Error return*/
	}
	UpdateShiftInfo =1;
}

void SHIFT::run()
{
	shiftCalculation();
}

