/*
 * UARTTxRxHandle.c
 *
 *  Created on: Jan 21, 2023
 *      Author: MKS
 */
#include"main.h"

extern UART_HandleTypeDef hlpuart1;
extern UART_HandleTypeDef huart1;
extern uint8_t rxTempBuff[5];
extern uint8_t u8rxbuf[16];
uint8_t checkbuff[300];
uint8_t refinc;
uint8_t rx_msb_data,rx_lsb_data,rx_msb_h_data,rx_seq,rx_meter_id;
uint8_t rx_seq_1;
uint8_t rx_msb_data_w,rx_lsb_data_w;

uint16_t Dye_Temperature;
uint16_t Connector_Temperature;
extern uint16_t act_temperature_c1,act_temperature_c2,act_temperature_c3,act_temperature_c4;
uint16_t water_temperature;


extern uint8_t Rxseqdecoder;
extern void ESPRxDecoder(unsigned char Rxwifi_data,unsigned char Rxseqdecoder);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &hlpuart1)
	{
		ESPRxDecoder(rxTempBuff[0],Rxseqdecoder);

		HAL_UART_Receive_IT(&hlpuart1,rxTempBuff,1);
	}

	if(huart == &huart1)
	{
		if(((u8rxbuf[0]==0x01)||(u8rxbuf[0]==0x02)||(u8rxbuf[0]==0x03)||(u8rxbuf[0]==0x04))&&
				(rx_seq==0))
		{
			rx_seq=1;
			rx_meter_id = u8rxbuf[0];
		}
		else if((rx_seq==1)&&(u8rxbuf[0]==0x03))
		{
			rx_seq=2;
		}
		else if((rx_seq==2)&&(u8rxbuf[0]==0x01))
		{
			rx_seq=3;
		}
		else if(rx_seq==3)
		{
			rx_msb_h_data =u8rxbuf[0];
			rx_seq=4;
		}
		else if(rx_seq==4)
		{
			rx_seq=5;
			rx_msb_data = u8rxbuf[0];
		}
		else if(rx_seq==5)
		{
			rx_lsb_data =u8rxbuf[0];
			if(rx_meter_id==1){act_temperature_c1 = (rx_msb_h_data<<16 |rx_msb_data<<8 | rx_lsb_data); }
			else if(rx_meter_id==2){act_temperature_c2 = (rx_msb_h_data<<16 |rx_msb_data<<8 | rx_lsb_data); }
			else if(rx_meter_id==3){act_temperature_c3 = (rx_msb_h_data<<16 |rx_msb_data<<8 | rx_lsb_data); }
			else if(rx_meter_id==4){act_temperature_c4 = (rx_msb_h_data<<16 |rx_msb_data<<8 | rx_lsb_data); }
			else{}
			rx_seq=0;
		}
		else
		{
			rx_seq=0;
		}

		if((u8rxbuf[0] == 0x05)&&(rx_seq_1 == 0x0))
		{
			rx_seq_1=1;
		}
		else if((u8rxbuf[0] == 0x03)&&(rx_seq_1 == 0x1))
		{
			rx_seq_1=2;
		}
		else if((rx_seq_1==2)&&(u8rxbuf[0]==0x08))
		{
			rx_seq_1=3;
		}
		else if(rx_seq_1==3)
		{
			rx_msb_data_w =u8rxbuf[0];
			rx_seq_1=4;
		}
		else if(rx_seq_1==4)
		{
			rx_seq_1=5;
			rx_lsb_data_w = u8rxbuf[0];
			water_temperature = (rx_msb_data_w<<8 | rx_lsb_data_w);
		}
		HAL_UART_Receive_IT(&huart1,u8rxbuf,1);
	}
}



