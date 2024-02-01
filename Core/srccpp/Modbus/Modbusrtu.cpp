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
constexpr uint8_t multipleWriteRequestH = 0x4E;
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
extern uint8_t Rx_Dwin_Complete;
extern uint8_t Dwinseq;
extern uint8_t DwinDatabuffer[255];
extern uint16_t ProcessId_Value;;

uint8_t TxSeqComplete;
uint8_t ProcRunning,Idle_State;
uint8_t indexStartUsername,indexStartPsw;
uint8_t noOfByteUsername,noOfBytePsw;
uint8_t wifiUsername[15],wifiPassword[15];
uint8_t noOfByteUsernameK1,noOfBytePswK1;
uint8_t wifiUsernameK1[15],wifiPasswordK1[15];
uint8_t UpdateMemoryForWfi;
uint8_t check_valid;
uint8_t dwinMachineId,dwinBatchReset,dwinBatchResetRequest;
uint8_t dwinMachineId_k1,dwinBatchReset_k1;
uint8_t UpdateMachineframe;

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

		u8ModbusRegisterdwin[14] = highByte(temperature_reference);
		u8ModbusRegisterdwin[15] = lowByte(temperature_reference);
		u8ModbusRegisterdwin[16] = highByte(temperature_reference);
		u8ModbusRegisterdwin[17] = lowByte(temperature_reference);
		u8ModbusRegisterdwin[18] = highByte(temperature_reference);
		u8ModbusRegisterdwin[19] = lowByte(temperature_reference);
		u8ModbusRegisterdwin[20] = highByte(temperature_reference);
		u8ModbusRegisterdwin[21] = lowByte(temperature_reference);//2007

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

		if(start_process_control_timer == 1){ProcRunning=1;Idle_State=0;}
		else if(start_process_control_timer ==2){ProcRunning=2;Idle_State=0;}
		else{ProcRunning=0;Idle_State=1;}

		u8ModbusRegisterdwin[32] = highByte(ProcRunning);//1
		u8ModbusRegisterdwin[33] = lowByte(ProcRunning);
//Timer status
		u8ModbusRegisterdwin[34] = highByte(Idle_State);//0
		u8ModbusRegisterdwin[35] = lowByte(Idle_State);
		if(start_process_control_timer==1){
		u8ModbusRegisterdwin[36] = highByte(seq1_remaining_time_Hr);
		u8ModbusRegisterdwin[37] = lowByte(seq1_remaining_time_Hr);
		u8ModbusRegisterdwin[38] = highByte(seq1_remaining_time_min);
		u8ModbusRegisterdwin[39] = lowByte(seq1_remaining_time_min);}
		else if(start_process_control_timer==2){
		u8ModbusRegisterdwin[36] = highByte(seq2_remaining_time_Hr);
		u8ModbusRegisterdwin[37] = lowByte(seq2_remaining_time_Hr);
		u8ModbusRegisterdwin[38] = highByte(seq2_remaining_time_min);
		u8ModbusRegisterdwin[39] = lowByte(seq2_remaining_time_min);}
		else{
		u8ModbusRegisterdwin[36] = highByte(0);
		u8ModbusRegisterdwin[37] = lowByte(0);
		u8ModbusRegisterdwin[38] = highByte(0);
		u8ModbusRegisterdwin[39] = lowByte(0);}

		u8ModbusRegisterdwin[40] = highByte(0);
		u8ModbusRegisterdwin[41] = lowByte(0);
		u8ModbusRegisterdwin[42] = highByte(0);
		u8ModbusRegisterdwin[43] = lowByte(0);
		u8ModbusRegisterdwin[44] = highByte(0);
		u8ModbusRegisterdwin[45] = lowByte(0);
		u8ModbusRegisterdwin[46] = highByte(0);
		u8ModbusRegisterdwin[47] = lowByte(0);
		u8ModbusRegisterdwin[48] = highByte(0);
		u8ModbusRegisterdwin[49] = lowByte(0);
		u8ModbusRegisterdwin[50] = highByte(0);
		u8ModbusRegisterdwin[51] = lowByte(10);
		u8ModbusRegisterdwin[52] = highByte(10);
		u8ModbusRegisterdwin[53] = lowByte(20);
		u8ModbusRegisterdwin[54] = highByte(20);
		u8ModbusRegisterdwin[55] = lowByte(30);
		u8ModbusRegisterdwin[56] = highByte(30);
		u8ModbusRegisterdwin[57] = lowByte(40);
		u8ModbusRegisterdwin[58] = highByte(40);
		u8ModbusRegisterdwin[59] = lowByte(50);
		u8ModbusRegisterdwin[60] = highByte(50);
		u8ModbusRegisterdwin[61] = lowByte(60);
		u8ModbusRegisterdwin[62] = highByte(60);
		u8ModbusRegisterdwin[63] = lowByte(70);
		u8ModbusRegisterdwin[64] = highByte(70);
		u8ModbusRegisterdwin[65] = lowByte(80);
		u8ModbusRegisterdwin[66] = highByte(80);
		u8ModbusRegisterdwin[67] = lowByte(90);
		u8ModbusRegisterdwin[68] = highByte(90);
		u8ModbusRegisterdwin[69] = lowByte(100);
		u8ModbusRegisterdwin[70] = highByte(100);
		u8ModbusRegisterdwin[71] = lowByte(200);
		u8ModbusRegisterdwin[72] = highByte(200);
		u8ModbusRegisterdwin[73] = lowByte(ProcessId_Value);
		u8ModbusRegisterdwin[74] = highByte(ProcessId_Value);
		u8ModbusRegisterdwin[75] = lowByte(ProcessId_Value);
		u8ModbusRegisterdwin[76] = highByte(ProcessId_Value);
		u8ModbusRegisterdwin[77] = lowByte(ProcessId_Value);

		noOfDataDwin=78;
		Cntid_dwin=1;
	break;
	case 1:
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

			u8ModbusRegisterdwin[14] = highByte(temperature_reference);
			u8ModbusRegisterdwin[15] = lowByte(temperature_reference);
			u8ModbusRegisterdwin[16] = highByte(temperature_reference);
			u8ModbusRegisterdwin[17] = lowByte(temperature_reference);
			u8ModbusRegisterdwin[18] = highByte(temperature_reference);
			u8ModbusRegisterdwin[19] = lowByte(temperature_reference);
			u8ModbusRegisterdwin[20] = highByte(temperature_reference);
			u8ModbusRegisterdwin[21] = lowByte(temperature_reference);//2007

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

			if(start_process_control_timer == 1){ProcRunning=1;Idle_State=0;}
			else if(start_process_control_timer ==2){ProcRunning=2;Idle_State=0;}
			else{ProcRunning=0;Idle_State=1;}

			u8ModbusRegisterdwin[32] = highByte(ProcRunning);//1
			u8ModbusRegisterdwin[33] = lowByte(ProcRunning);
	//Timer status
			u8ModbusRegisterdwin[34] = highByte(Idle_State);//0
			u8ModbusRegisterdwin[35] = lowByte(Idle_State);
			if(start_process_control_timer==1){
			u8ModbusRegisterdwin[36] = highByte(seq1_remaining_time_Hr);
			u8ModbusRegisterdwin[37] = lowByte(seq1_remaining_time_Hr);
			u8ModbusRegisterdwin[38] = highByte(seq1_remaining_time_min);
			u8ModbusRegisterdwin[39] = lowByte(seq1_remaining_time_min);}
			else if(start_process_control_timer==2){
			u8ModbusRegisterdwin[36] = highByte(seq2_remaining_time_Hr);
			u8ModbusRegisterdwin[37] = lowByte(seq2_remaining_time_Hr);
			u8ModbusRegisterdwin[38] = highByte(seq2_remaining_time_min);
			u8ModbusRegisterdwin[39] = lowByte(seq2_remaining_time_min);}
			else{
			u8ModbusRegisterdwin[36] = highByte(0);
			u8ModbusRegisterdwin[37] = lowByte(0);
			u8ModbusRegisterdwin[38] = highByte(0);
			u8ModbusRegisterdwin[39] = lowByte(0);}

			u8ModbusRegisterdwin[40] = highByte(0);
			u8ModbusRegisterdwin[41] = lowByte(0);
			u8ModbusRegisterdwin[42] = highByte(0);
			u8ModbusRegisterdwin[43] = lowByte(0);
			u8ModbusRegisterdwin[44] = highByte(0);
			u8ModbusRegisterdwin[45] = lowByte(0);
			u8ModbusRegisterdwin[46] = highByte(0);
			u8ModbusRegisterdwin[47] = lowByte(0);
			u8ModbusRegisterdwin[48] = highByte(0);
			u8ModbusRegisterdwin[49] = lowByte(0);
			u8ModbusRegisterdwin[50] = highByte(0);
			u8ModbusRegisterdwin[51] = lowByte(10);
			u8ModbusRegisterdwin[52] = highByte(10);
			u8ModbusRegisterdwin[53] = lowByte(20);
			u8ModbusRegisterdwin[54] = highByte(20);
			u8ModbusRegisterdwin[55] = lowByte(30);
			u8ModbusRegisterdwin[56] = highByte(30);
			u8ModbusRegisterdwin[57] = lowByte(40);
			u8ModbusRegisterdwin[58] = highByte(40);
			u8ModbusRegisterdwin[59] = lowByte(50);
			u8ModbusRegisterdwin[60] = highByte(50);
			u8ModbusRegisterdwin[61] = lowByte(60);
			u8ModbusRegisterdwin[62] = highByte(60);
			u8ModbusRegisterdwin[63] = lowByte(70);
			u8ModbusRegisterdwin[64] = highByte(70);
			u8ModbusRegisterdwin[65] = lowByte(80);
			u8ModbusRegisterdwin[66] = highByte(80);
			u8ModbusRegisterdwin[67] = lowByte(90);
			u8ModbusRegisterdwin[68] = highByte(90);
			u8ModbusRegisterdwin[69] = lowByte(100);
			u8ModbusRegisterdwin[70] = highByte(100);
			u8ModbusRegisterdwin[71] = lowByte(200);
			u8ModbusRegisterdwin[72] = highByte(200);
			u8ModbusRegisterdwin[73] = lowByte(ProcessId_Value);
			u8ModbusRegisterdwin[74] = highByte(ProcessId_Value);
			u8ModbusRegisterdwin[75] = lowByte(ProcessId_Value);
			u8ModbusRegisterdwin[76] = highByte(ProcessId_Value);
			u8ModbusRegisterdwin[77] = lowByte(ProcessId_Value);

			noOfDataDwin=78;
			Cntid_dwin=2;
		break;
	case 2:
			u8ModbusRegisterdwin[0] = START_BYTE_1;
			u8ModbusRegisterdwin[1] = START_BYTE_2;
			u8ModbusRegisterdwin[2] = multipleReadRequestH;
			u8ModbusRegisterdwin[3] = multipleReadRequestL;
			u8ModbusRegisterdwin[4] = 0x30;
			u8ModbusRegisterdwin[5] = 0x09;
			u8ModbusRegisterdwin[6] = 0x0a;
			Dwinseq=0;
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
void Modbusrtu::dwinDecoderMachineFrame(void)
{
	if(Rx_Dwin_Complete==0){return;}
	Rx_Dwin_Complete=0;

	if(DwinDatabuffer[4] != 0)
	{
		dwinMachineId = DwinDatabuffer[4];
		dwinBatchReset = DwinDatabuffer[6];
		dwinBatchResetRequest = DwinDatabuffer[8];
		if(dwinMachineId != dwinMachineId_k1){
			UpdateMachineframe =1;
			dwinMachineId_k1 = dwinMachineId;
		}
		if(dwinBatchReset != dwinBatchReset_k1){
					UpdateMachineframe =1;
					dwinBatchReset_k1 = dwinBatchReset;
		}
	}

}
void Modbusrtu::dwinDecoder(void)
{
	if(Rx_Dwin_Complete==1)
	{
	Rx_Dwin_Complete=0;
	for(uint8_t i=0;i<=200;i++)
	{
		if(DwinDatabuffer[i] == 0x00)
		{
			++check_valid ;
		}
	}
	if(check_valid >15){return;}
	check_valid=0;
	for(uint8_t i=0;i<=20;i++)
	{
		if(DwinDatabuffer[i] == 0x5A)
		{
			indexStartUsername = i;
			break;
		}
	}

	noOfByteUsername = DwinDatabuffer[indexStartUsername+1];
	if((noOfByteUsername==0)||(noOfByteUsername>20)){return;}
	for(uint8_t i=0;i<noOfByteUsername;i++){
		wifiUsername[i] = DwinDatabuffer[(indexStartUsername+2)+i];
	}

	for(uint8_t i=(indexStartUsername+noOfByteUsername);i<=255;i++)
	{
		if(DwinDatabuffer[i] == 0x5A)
		{
			indexStartPsw = i;
			break;
		}
	}

	noOfBytePsw = DwinDatabuffer[indexStartPsw+1];
	if((noOfBytePsw ==0)||(noOfBytePsw>20)){return;}
	for(uint8_t i=0;i<noOfBytePsw;i++){
		wifiPassword[i] = DwinDatabuffer[(indexStartPsw+2)+i];
	}

	if(noOfByteUsernameK1 != noOfByteUsername){
		UpdateMemoryForWfi=1;
	}
	if(noOfBytePswK1 != noOfBytePsw){
		UpdateMemoryForWfi=1;
	}
	for(uint8_t i=0;i<noOfByteUsername;i++)
	{
		if(wifiUsernameK1[i] != wifiUsername[i]){
			UpdateMemoryForWfi=1;
			break;
		}
	}
	for(uint8_t i=0;i<noOfBytePsw;i++)
	{
		if(wifiPasswordK1[i] != wifiPassword[i]){
			UpdateMemoryForWfi=1;
			break;
		}
	}

	if(UpdateMemoryForWfi==1){
		noOfByteUsernameK1 = noOfByteUsername;
		for(uint8_t i=0;i<noOfByteUsername;i++){
			wifiUsernameK1[i] = wifiUsername[i];
		}
		noOfBytePswK1 = noOfBytePsw;
		for(uint8_t i=0;i<noOfBytePsw;i++){
			wifiPasswordK1[i] = wifiPassword[i];
		}
	}
    }
}

