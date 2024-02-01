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
	void sim();
	void stateMachineProcessControl();
	void specialHandler();
	void InputHandler();
	void resetBatchId();

private:
	uint8_t m_sequencestate;
	GPIO_PinState m_machineinput;
	GPIO_PinState m_waterInput;
	GPIO_PinState m_quenchtrigger;
	uint16_t m_temeperatureUpperBound;
	uint16_t m_temperatureLowerBound;
	uint16_t Data1_RxData=0;
};

#endif /* SRCCPP_HEATTREATMENTLOGIC_APPLICATIONSW_H_ */
