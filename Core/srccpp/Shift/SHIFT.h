/*
 * SHIFT.h
 *
 *  Created on: 15-Feb-2023
 *      Author: MKS
 */

#ifndef SRCCPP_SHIFT_SHIFT_H_
#define SRCCPP_SHIFT_SHIFT_H_

class SHIFT {
public:
	SHIFT();
	virtual ~SHIFT();
	void run();
private:
	void shiftCalculation(void);
	uint16_t TotalMinutesvar,Shift1_OnTime,Shift1_OffTime;
	uint16_t Shift2_OnTime,shift2_buffer_time_1,Shift2_OffTime;
	uint16_t Shift3_OnTime,Shift3_OffTime;
	uint16_t locTimeTotal,onlineTimeTotal;
};

#endif /* SRCCPP_SHIFT_SHIFT_H_ */
