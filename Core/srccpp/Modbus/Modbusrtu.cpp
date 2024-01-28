/*
 * Modbusrtu.cpp
 *
 *  Created on: 07-Jan-2023
 *      Author: MKS
 */

#include "Modbusrtu.h"
#include "Modbus_types.h"
#include "baselib.h"

extern uint16_t temperature_reference;
constexpr uint16_t Step1_Temperature_Add= 0x01;
constexpr uint16_t Step1_Time_Add= 4097;
constexpr uint16_t Step2_Temperature_Add= 4099;
constexpr uint16_t Step2_Time_Add= 4100;

constexpr uint8_t START_BYTE_1=0x5A;
constexpr uint8_t START_BYTE_2=0xA5;
constexpr uint8_t multipleWriteRequestH = 0x28;
constexpr uint8_t multipleWriteRequestL = 0x82;
constexpr uint8_t multipleReadRequestH = 0x04;
constexpr uint8_t multipleReadRequestL = 0x83;

constexpr uint8_t WaterTemperatureId=0x05;
extern uint16_t Temp_Rising_Reference;
extern uint8_t TimeReference_Hr,TimeReference_Min,Time_Rising_Ref_Hr,Time_Rising_Ref_Min;
extern uint16_t temperature_reference;
extern uint16_t act_temperature_c1,act_temperature_c2,act_temperature_c3,act_temperature_c4;
extern uint16_t Temperature_High_Http,Temperature_Low_Http,R_Temperature_High_Http,R_Temperature_Low_Http;
extern uint8_t H_Timer01HrValue,H_Timer01MinValue,H_Timer02HrValue,H_Timer02MinValue;
extern uint8_t Rise_Sequence1_Hour,Rise_Sequence1_Minute,Rise_Sequence2_Hour,Rise_Sequence2_Minute;
extern uint8_t start_process_control_timer;
extern uint8_t seq1_remaining_time_Hr,seq1_remaining_time_min,seq2_remaining_time_Hr,seq2_remaining_time_min;

uint8_t TxSeqComplete;
uint8_t SolunishingRunning,PrecipitationRun,Idle_State;
uint8_t Rx_Dwin_Point;

Modbusrtu::Modbusrtu() {
	// TODO Auto-generated constructor stub

}

Modbusrtu::~Modbusrtu() {
	// TODO Auto-generated destructor stub
}

void Modbusrtu::ModbusReadTransaction(void)
{
	m_settemperature = temperature_reference*10;
	switch(Cntid)
	{
	case 0:
		_u8MBSlave 			= mTemperatureSensorId;
		u8MBFunction 		= 0x03;
		_u16ReadAddress 	= 0x00;
		_u16ReadQty     	= 0x01;
		u8ModbusRegister[0] = _u8MBSlave;
		u8ModbusRegister[1] =  u8MBFunction;
		u8ModbusRegister[2] =  0x01;
		u8ModbusRegister[3] =  static_cast<uint8_t>((_u16ReadAddress & 0xff00)>>8);
		u8ModbusRegister[4] =  static_cast<uint8_t>(_u16ReadAddress & 0x00ff);
		u8ModbusRegister[5] = _u16ReadQty;
		u16CRC 				= ASCChecksum(u8ModbusRegister,6);
		u8ModbusRegister[6] = static_cast<uint8_t>(u16CRC & 0x00ff);
		u8ModbusRegister[7] = static_cast<uint8_t>((u16CRC & 0xff00)>>8);

		Cntid=1;
	break;
	case 1:/*RISING TEMP SET POINT*/
		_u8MBSlave 			= mTemperatureSensorId;
		u8MBFunction 		= 0x06;
		u8ModbusRegister[0] = _u8MBSlave;
		u8ModbusRegister[1] =  u8MBFunction;
		u8ModbusRegister[2] = 0x00;
		u8ModbusRegister[3] = 0x01;
		m_settemperature = Temp_Rising_Reference;
		u8ModbusRegister[4] = static_cast<uint8_t>((m_settemperature & 0xff00)>>8);
		u8ModbusRegister[5] = static_cast<uint8_t>(m_settemperature & 0x00ff);
		u16CRC 				= ASCChecksum(u8ModbusRegister,6);
		u8ModbusRegister[6] = static_cast<uint8_t>(u16CRC & 0x00ff);
		u8ModbusRegister[7] = static_cast<uint8_t>((u16CRC & 0xff00)>>8);
		Cntid=2;
	break;
	case 2:/*RISING TIME SET*/
			_u8MBSlave 			= mTemperatureSensorId;
			u8MBFunction 		= 0x06;
			u8ModbusRegister[0] = _u8MBSlave;
			u8ModbusRegister[1] =  u8MBFunction;
			u8ModbusRegister[2] = 0x10;
			u8ModbusRegister[3] = 0x01;
			m_setTime = ((Time_Rising_Ref_Hr*60)+ Time_Rising_Ref_Min)+0;
			u8ModbusRegister[4] = static_cast<uint8_t>((m_setTime & 0xff00)>>8);
			u8ModbusRegister[5] = static_cast<uint8_t>(m_setTime & 0x00ff);
			u16CRC 				= ASCChecksum(u8ModbusRegister,6);
			u8ModbusRegister[6] = static_cast<uint8_t>(u16CRC & 0x00ff);
			u8ModbusRegister[7] = static_cast<uint8_t>((u16CRC & 0xff00)>>8);
			Cntid=3;
		break;
	case 3: /*HOLDING TEMP SET POINT 2*/
			_u8MBSlave 			= mTemperatureSensorId;
			u8MBFunction 		= 0x06;
			u8ModbusRegister[0] = _u8MBSlave;
			u8ModbusRegister[1] =  u8MBFunction;
			u8ModbusRegister[2] = 0x10;
			u8ModbusRegister[3] = 0x03;
			m_settemperature = temperature_reference;
			u8ModbusRegister[4] = static_cast<uint8_t>((m_settemperature & 0xff00)>>8);
			u8ModbusRegister[5] = static_cast<uint8_t>(m_settemperature & 0x00ff);
			u16CRC 				= ASCChecksum(u8ModbusRegister,6);
			u8ModbusRegister[6] = static_cast<uint8_t>(u16CRC & 0x00ff);
			u8ModbusRegister[7] = static_cast<uint8_t>((u16CRC & 0xff00)>>8);
			Cntid=4;

		break;
	case 4: /*HOLDING time SET 2*/
			_u8MBSlave 			= mTemperatureSensorId;
			u8MBFunction 		= 0x06;
			u8ModbusRegister[0] = _u8MBSlave;
			u8ModbusRegister[1] =  u8MBFunction;
			u8ModbusRegister[2] = 0x10;
			u8ModbusRegister[3] = 0x04;
			m_setTime = ((TimeReference_Hr*60)+ TimeReference_Min)+60;
			u8ModbusRegister[4] = static_cast<uint8_t>((m_setTime & 0xff00)>>8);
			u8ModbusRegister[5] = static_cast<uint8_t>(m_setTime & 0x00ff);
			u16CRC 				= ASCChecksum(u8ModbusRegister,6);
			u8ModbusRegister[6] = static_cast<uint8_t>(u16CRC & 0x00ff);
			u8ModbusRegister[7] = static_cast<uint8_t>((u16CRC & 0xff00)>>8);
			Cntid=5;
			if(mTemperatureSensorId ==1){mTemperatureSensorId=2;}
			else if(mTemperatureSensorId ==2){mTemperatureSensorId=3;}
			else if(mTemperatureSensorId ==3){mTemperatureSensorId=4;}
			else{mTemperatureSensorId=1;}
	break;
	case 5:
			u8MBFunction		= 0x03;
			_u16WriteAddress 	= 0x00;
			_u16ReadAddress  	= 0x04;
			u8ModbusRegister[0] = WaterTemperatureId;
			u8ModbusRegister[1] =  u8MBFunction;
			u8ModbusRegister[2] = static_cast<uint8_t>((_u16WriteAddress & 0xff00)>>8);
			u8ModbusRegister[3] = static_cast<uint8_t>(_u16WriteAddress & 0x00ff);
			u8ModbusRegister[4] = static_cast<uint8_t>((_u16ReadAddress & 0xff00)>>8);
			u8ModbusRegister[5] = static_cast<uint8_t>(_u16ReadAddress & 0x00ff);
			u16CRC 				= ASCChecksum(u8ModbusRegister,6);
			u8ModbusRegister[6] = static_cast<uint8_t>(u16CRC & 0x00ff);
			u8ModbusRegister[7] = static_cast<uint8_t>((u16CRC & 0xff00)>>8);
			Cntid=0;
	break;
	default:
		Cntid=0;
		mTemperatureSensorId=1;
	break;
	}


	//out_read_rxint_set.Noofbytesrx = (_u16ReadQty*2)+5;
	HAL_UART_Transmit_IT(&huart1,u8ModbusRegister,8);

}
//Hardware callback
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	//HAL_UART_Receive_IT(&huart1,u8rxbuf,13);
}

uint16_t Modbusrtu::ASCChecksum(uint8_t *ASCSrc, uint8_t NoOfBytes)
{
	uint8_t i, CheckSumBytes;
	uint8_t CRCRegLow = 0xff;
	uint8_t CRCRegHigh = 0xff;
	uint8_t CRCIndex;

	CheckSumBytes = NoOfBytes;
   	for(i=0;i < CheckSumBytes;i++)
   	{
	    CRCIndex = CRCRegLow ^ *ASCSrc++; 				//TransmittingData[i];
		CRCRegLow = CRCRegHigh ^ CRCArrayHigh[CRCIndex];
		CRCRegHigh = CRCArrayLow[CRCIndex];

	}
	return (CRCRegHigh << 8 | CRCRegLow );
}

/*Dwin frame*/
void Modbusrtu::dwinFrame(void)
{
	switch(Cntid_dwin)
	{
	case 0:
		u8ModbusRegisterdwin[0] = START_BYTE_1;
		u8ModbusRegisterdwin[1] = START_BYTE_2;
		u8ModbusRegisterdwin[2] = multipleWriteRequestH;
		u8ModbusRegisterdwin[3] = multipleWriteRequestL;
		u8ModbusRegisterdwin[4] = 0x20;
		u8ModbusRegisterdwin[5] = 0x00;
		u8ModbusRegisterdwin[6] = highByte(act_temperature_c1);
		u8ModbusRegisterdwin[7] = lowByte(act_temperature_c1);
		u8ModbusRegisterdwin[8] = highByte(act_temperature_c2);
		u8ModbusRegisterdwin[9] = lowByte(act_temperature_c2);
		u8ModbusRegisterdwin[10] = highByte(act_temperature_c3);
		u8ModbusRegisterdwin[11] = lowByte(act_temperature_c3);
		u8ModbusRegisterdwin[12] = highByte(act_temperature_c4);
		u8ModbusRegisterdwin[13] = lowByte(act_temperature_c4);

		u8ModbusRegisterdwin[14] = highByte(Temperature_High_Http);
		u8ModbusRegisterdwin[15] = lowByte(Temperature_High_Http);
		u8ModbusRegisterdwin[16] = highByte(Temperature_Low_Http);
		u8ModbusRegisterdwin[17] = lowByte(Temperature_Low_Http);
		u8ModbusRegisterdwin[18] = highByte(R_Temperature_High_Http);
		u8ModbusRegisterdwin[19] = lowByte(R_Temperature_High_Http);
		u8ModbusRegisterdwin[20] = highByte(R_Temperature_Low_Http);
		u8ModbusRegisterdwin[21] = lowByte(R_Temperature_Low_Http);//2007

		u8ModbusRegisterdwin[22] = highByte(0);
		u8ModbusRegisterdwin[23] = lowByte(1);//2008

		u8ModbusRegisterdwin[24] = highByte(H_Timer01HrValue);
		u8ModbusRegisterdwin[25] = lowByte(H_Timer01HrValue);
		u8ModbusRegisterdwin[26] = highByte(H_Timer01MinValue);
		u8ModbusRegisterdwin[27] = lowByte(H_Timer01MinValue);
		u8ModbusRegisterdwin[28] = highByte(H_Timer02HrValue);
		u8ModbusRegisterdwin[29] = lowByte(H_Timer02HrValue);
		u8ModbusRegisterdwin[30] = highByte(H_Timer02MinValue);
		u8ModbusRegisterdwin[31] = lowByte(H_Timer02MinValue);

		if(start_process_control_timer == 1){SolunishingRunning=1;PrecipitationRun=0;Idle_State=0;}
		else if(start_process_control_timer ==2){SolunishingRunning=0;PrecipitationRun=2;Idle_State=0;}
		else{SolunishingRunning=0;PrecipitationRun=0;Idle_State=1;}

		u8ModbusRegisterdwin[32] = highByte(SolunishingRunning);//1
		u8ModbusRegisterdwin[33] = lowByte(SolunishingRunning);
		u8ModbusRegisterdwin[34] = highByte(PrecipitationRun);//2
		u8ModbusRegisterdwin[35] = lowByte(PrecipitationRun);
//Timer status
		u8ModbusRegisterdwin[36] = highByte(Idle_State);//0
		u8ModbusRegisterdwin[37] = lowByte(Idle_State);
		if(start_process_control_timer==1){
		u8ModbusRegisterdwin[38] = highByte(seq1_remaining_time_Hr);
		u8ModbusRegisterdwin[39] = lowByte(seq1_remaining_time_Hr);
		u8ModbusRegisterdwin[40] = highByte(seq1_remaining_time_min);
		u8ModbusRegisterdwin[41] = lowByte(seq1_remaining_time_min);}
		else if(start_process_control_timer==2){
		u8ModbusRegisterdwin[38] = highByte(seq2_remaining_time_Hr);
		u8ModbusRegisterdwin[39] = lowByte(seq2_remaining_time_Hr);
		u8ModbusRegisterdwin[40] = highByte(seq2_remaining_time_min);
		u8ModbusRegisterdwin[41] = lowByte(seq2_remaining_time_min);}
		else{
		u8ModbusRegisterdwin[38] = highByte(0);
		u8ModbusRegisterdwin[39] = lowByte(0);
		u8ModbusRegisterdwin[40] = highByte(0);
		u8ModbusRegisterdwin[41] = lowByte(0);}


		noOfDataDwin=42;
		Cntid_dwin=1;
	break;
	case 1:
			u8ModbusRegisterdwin[0] = START_BYTE_1;
			u8ModbusRegisterdwin[1] = START_BYTE_2;
			u8ModbusRegisterdwin[2] = multipleReadRequestH;
			u8ModbusRegisterdwin[3] = multipleReadRequestL;
			u8ModbusRegisterdwin[4] = 0x30;
			u8ModbusRegisterdwin[5] = 0x00;
			u8ModbusRegisterdwin[6] = 0x16;
			Rx_Dwin_Point=0;
			noOfDataDwin=7;
			Cntid_dwin=0;
		break;
		default:
			Cntid_dwin=0;
		break;
		}
		//out_read_rxint_set.Noofbytesrx = (_u16ReadQty*2)+5;
		HAL_UART_Transmit_IT(&huart2,u8ModbusRegisterdwin,noOfDataDwin);
}
