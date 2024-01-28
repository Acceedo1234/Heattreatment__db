#include <HeattreatmentLogic/ApplicationSW.h>
#include "main.h"
#include "GLCD.h"
#include "Modbusrtu.h"
#include "DisplayRoutine.h"
#include "OfflineStorage.h"
#include "ESP8266.h"
#include "SHIFT.h"
#include <stdio.h>
#include <string.h>
using namespace std;

extern "C" {
void Send_WifiCmd(void);
void W25qxx_EraseChip(void);
void ESPRXDataSeg(void);
void ReadOnlineData(void);
void ethernetHTTPRoutine(void);
void initializeHttp(void);
}

extern uint8_t TxSeqComplete;
extern uint8_t Flag1Second;
extern uint8_t Flag1MS;
extern uint8_t Flag100milliSeconds;

/**
  * @brief  The application entry point for cpp
  * @retval int
  */
//TIM_HandleTypeDef htim6;
void cppMain()
{
	GLCD glcd;
	Modbusrtu ModbusInst;
	DisplayRoutine displayRoutineInst;
	Heattreatment heattreatmentInst;
	OfflineStorage offlineStorageInst;
	ESP8266 esp8266Inst;
//	SHIFT shiftInst;
	offlineStorageInst.ReadOfflinedataInit();
	displayRoutineInst.Init();
	esp8266Inst.Init();

	TxSeqComplete=1;


	while(1)
	{

		if(Flag1MS)
		{
			Flag1MS=0;
			heattreatmentInst.run();

		}
		if(Flag100milliSeconds)
		{
			Flag100milliSeconds=0;
			offlineStorageInst.run();
			ModbusInst.ModbusReadTransaction();
		}
		if(Flag1Second)
		{
			Flag1Second=0;
			displayRoutineInst.run();
			esp8266Inst.run();
			heattreatmentInst.sim();
		}
	}
}
