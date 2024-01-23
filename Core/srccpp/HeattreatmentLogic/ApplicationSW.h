/*
 * LpdcLogic.h
 *
 *  Created on: 04-Feb-2023
 *      Author: MKS
 */

#ifndef SRCCPP_HEATTREATMENTLOGIC_APPLICATIONSW_H_
#define SRCCPP_HEATTREATMENTLOGIC_APPLICATIONSW_H_


#include "main.h"

class Heattreatment {
public:
	Heattreatment();
	virtual ~Heattreatment();
	void run();
	void stateMachineProcessControl();


private:
	uint8_t m_sequencestate;
	GPIO_PinState m_simEndProcess;
	uint16_t m_temeperatureUpperBound;
	uint16_t m_temperatureLowerBound;
};

#endif /* SRCCPP_HEATTREATMENTLOGIC_APPLICATIONSW_H_ */
