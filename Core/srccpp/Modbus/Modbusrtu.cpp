/*
 * Modbusrtu.cpp
 *
 *  Created on: 07-Jan-2023
 *      Author: MKS
 */

#include "Modbusrtu.h"
#include "Modbus_types.h"

extern uint16_t temperature_reference;
constexpr uint16_t Step1_Temperature_Add= 0x01;
constexpr uint16_t Step1_Time_Add= 4097;
constexpr uint16_t Step2_Temperature_Add= 4099;
constexpr uint16_t Step2_Time_Add= 4100;

constexpr uint8_t WaterTemperatureId=0x05;
uint8_t TxSeqComplete;
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

	case 1:
		_u8MBSlave 			= mTemperatureSensorId;
		u8MBFunction 		= 0x06;
		_u16WriteAddress 	= Step1_Temperature_Add;
		u8ModbusRegister[0] = _u8MBSlave;
		u8ModbusRegister[1] =  u8MBFunction;
		u8ModbusRegister[2] = static_cast<uint8_t>((_u16WriteAddress & 0xff00)>>8);
		u8ModbusRegister[3] = static_cast<uint8_t>(_u16WriteAddress & 0x00ff);
		u8ModbusRegister[4] = static_cast<uint8_t>((m_settemperature & 0xff00)>>8);
		u8ModbusRegister[5] = static_cast<uint8_t>(m_settemperature & 0x00ff);
		u16CRC 				= ASCChecksum(u8ModbusRegister,6);
		u8ModbusRegister[6] = static_cast<uint8_t>(u16CRC & 0x00ff);
		u8ModbusRegister[7] = static_cast<uint8_t>((u16CRC & 0xff00)>>8);
		Cntid=2;
	break;
	case 2:
			_u8MBSlave 			= mTemperatureSensorId;
			u8MBFunction 		= 0x06;
			_u16WriteAddress 	= Step1_Time_Add;
			u8ModbusRegister[0] = _u8MBSlave;
			u8ModbusRegister[1] =  u8MBFunction;
			u8ModbusRegister[2] = static_cast<uint8_t>((_u16WriteAddress & 0xff00)>>8);
			u8ModbusRegister[3] = static_cast<uint8_t>(_u16WriteAddress & 0x00ff);
			u8ModbusRegister[4] = static_cast<uint8_t>(((m_settemperature+200) & 0xff00)>>8);
			u8ModbusRegister[5] = static_cast<uint8_t>((m_settemperature+200) & 0x00ff);
			u16CRC 				= ASCChecksum(u8ModbusRegister,6);
			u8ModbusRegister[6] = static_cast<uint8_t>(u16CRC & 0x00ff);
			u8ModbusRegister[7] = static_cast<uint8_t>((u16CRC & 0xff00)>>8);
			Cntid=3;
		break;
	case 3:
			_u8MBSlave 			= mTemperatureSensorId;
			u8MBFunction 		= 0x06;
			_u16WriteAddress 	= Step2_Temperature_Add;
			u8ModbusRegister[0] = _u8MBSlave;
			u8ModbusRegister[1] =  u8MBFunction;
			u8ModbusRegister[2] = static_cast<uint8_t>((_u16WriteAddress & 0xff00)>>8);
			u8ModbusRegister[3] = static_cast<uint8_t>(_u16WriteAddress & 0x00ff);
			u8ModbusRegister[4] = static_cast<uint8_t>(((m_settemperature-200) & 0xff00)>>8);
			u8ModbusRegister[5] = static_cast<uint8_t>((m_settemperature-200) & 0x00ff);
			u16CRC 				= ASCChecksum(u8ModbusRegister,6);
			u8ModbusRegister[6] = static_cast<uint8_t>(u16CRC & 0x00ff);
			u8ModbusRegister[7] = static_cast<uint8_t>((u16CRC & 0xff00)>>8);
			Cntid=4;

		break;
	case 4:
				_u8MBSlave 			= mTemperatureSensorId;
				u8MBFunction 		= 0x06;
				_u16WriteAddress 	= Step2_Time_Add;
				u8ModbusRegister[0] = _u8MBSlave;
				u8ModbusRegister[1] =  u8MBFunction;
				u8ModbusRegister[2] = static_cast<uint8_t>((_u16WriteAddress & 0xff00)>>8);
				u8ModbusRegister[3] = static_cast<uint8_t>(_u16WriteAddress & 0x00ff);
				u8ModbusRegister[4] = static_cast<uint8_t>(((m_settemperature+200) & 0xff00)>>8);
				u8ModbusRegister[5] = static_cast<uint8_t>((m_settemperature+200) & 0x00ff);
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
