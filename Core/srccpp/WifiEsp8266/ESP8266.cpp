/*
 * ESP8266.cpp
 *
 *  Created on: 09-Feb-2023
 *      Author: MKS
 */
#include "main.h"
#include "ESP8266.h"
#include <stdio.h>
#include <string.h>
using namespace std;

extern "C" {
void W25qxx_ReadSector(uint8_t *pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_SectorSize);
bool W25qxx_IsEmptySector(uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_SectorSize);
void W25qxx_WriteSector(uint8_t *pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_SectorSize);
void W25qxx_EraseSector(uint32_t SectorAddr);
}
extern UART_HandleTypeDef hlpuart1;

uint8_t wifi_command;
uint8_t ESP8266TXData[250];
uint8_t ContentData[250];
uint8_t OnlineData_buffer[200];
uint8_t bufferptr;
uint8_t Rxseqdecoder;
uint8_t Check_CWMODE_For_Hang;
uint16_t NoOfdata_byte;
uint8_t url_send;
uint8_t Timerdelay;
uint8_t url_buffer;
uint16_t Dyn_data_calc;
uint16_t ContentLength;
uint8_t RefreshBlockInfo;
uint8_t powercycleRefresh;
uint8_t NoOfBatch_to_Send,Framecheck;
uint8_t ProductionSet_uintFormat_MEM[850]={0};
uint16_t lenOfURl;
uint16_t r_set_duration_seq1,set_duration_seq1,r_set_duration_seq2,set_duration_seq2;
uint16_t remaining_duration_seq1,remaining_duration_seq2;
extern uint8_t BlockStatusOffline[40];
extern uint8_t ProductionSet_uintFormat[200];
extern uint16_t water_temperature;
extern uint16_t Rise_Sequence1_temp,Rise_Sequence2_temp;
extern uint8_t Rise_Sequence1_Hour,Rise_Sequence1_Minute,Rise_Sequence2_Hour,Rise_Sequence2_Minute;
extern uint8_t H_Timer01HrValue,H_Timer01MinValue,H_Timer02HrValue,H_Timer02MinValue;
extern uint8_t R_Sequence2_hour_http,R_Sequence2_minute_http,Sequence2_hour_http,Sequence2_minute_http;
extern uint8_t noOfByteUsername,noOfBytePsw;
extern uint8_t wifiUsername[15],wifiPassword[15];


ESP8266::ESP8266() {
	// TODO Auto-generated constructor stub

}

ESP8266::~ESP8266() {
	// TODO Auto-generated destructor stub
}


void ESP8266::run()
{
	Send_WifiCmd();

}

void ESP8266::Send_WifiCmd()
{
	switch(wifi_command)
	{
	case 5: //step --1 Reset COntroller PIN
		HAL_GPIO_WritePin(GPIOB, WIFIRST_Pin, GPIO_PIN_SET);
		HAL_Delay(1000);
		HAL_GPIO_WritePin(GPIOB, WIFIRST_Pin, GPIO_PIN_RESET);
		wifi_command=13;

	break;
	case 10://WI-Fi Reset
	NoOfdata_byte=7;
	wifi_command=13;
	Timerdelay=0;
	bufferptr=0;
	HAL_UART_Transmit_IT(&hlpuart1,CMDAtRst,NoOfdata_byte);
	break;
	case 11:
	if(++Timerdelay >12)
	{
		Timerdelay=0;
		wifi_command=14;
	}
	break;
	case 12:
	NoOfdata_byte=6;
	wifi_command=13;
	Timerdelay=0;
	HAL_UART_Transmit_IT(&hlpuart1,CMDAtEch0,NoOfdata_byte);
	break;
	case 13:
	if(++Timerdelay >15)
	{
		Timerdelay=0;
		wifi_command=20;
	}
	break;
	case 14:
	NoOfdata_byte=4;
	Rxseqdecoder=8;
	wifi_command=20;//default wait 30sec
	Timerdelay=0;
	HAL_UART_Transmit_IT(&hlpuart1,CMDATok,NoOfdata_byte);
	break;
	case 15:
	if(++Timerdelay >2)
	{
		Timerdelay=0;
	}
	break;
	case 20:   //CWMODE		//hardrest sequce//1.0 for wifi reset
	NoOfdata_byte=13;
	Rxseqdecoder=1;	  //add retry
	Timerdelay=0;
	bufferptr=0;
	HAL_UART_Transmit_IT(&hlpuart1,CMDATCWMODE,NoOfdata_byte);
	Check_CWMODE_For_Hang = Check_CWMODE_For_Hang+1;
	wifi_command=21;

	break;
	case 21:	//waiting for Ok  && if above 30 seconds resend command
	if(++Timerdelay >10)
	{
		Timerdelay=0;
		if(5 ==  Check_CWMODE_For_Hang)
		{
			wifi_command=5;	 //Hardware reset
			Check_CWMODE_For_Hang = 0;
		}
		else
		{
			wifi_command=10;
		}
	}
	break;
	case 30:   //CWJAP	   //userid-9digit,psw 8digit  //userid-5digit,psw 8digit
	//NoOfdata_byte=41;//32;
	Rxseqdecoder=2;
	wifi_command=41;
	Timerdelay=0;
	bufferptr=0;
	for(uint8_t i=0;i<=9;i++){
		CMDATCWJAPUsernamePsw[i]= CMDATCWJAPUsernamePswB1[i];
	}
	for(uint8_t i=10,j=0;j<=noOfByteUsername;i++,j++){
		CMDATCWJAPUsernamePsw[i]= wifiUsername[j];
	}
	for(uint8_t i=(10+noOfByteUsername),j=0;j<=2;i++,j++){
		CMDATCWJAPUsernamePsw[i]= CMDATCWJAPUsernamePswB2[j];
	}
	for(uint8_t i=(10+noOfByteUsername+3),j=0;j<=noOfBytePsw;i++,j++){
		CMDATCWJAPUsernamePsw[i]= wifiPassword[j];
	}
	for(uint8_t i=(10+noOfByteUsername+3+noOfBytePsw),j=0;j<=2;i++,j++){
		CMDATCWJAPUsernamePsw[i]= CMDATCWJAPUsernamePswB3[j];
	}
	NoOfdata_byte = 10+noOfByteUsername+3+noOfBytePsw+3;
	HAL_UART_Transmit_IT(&hlpuart1,CMDATCWJAPUsernamePsw,NoOfdata_byte);
	break;		   //add retry
	case 41:	   //resend if o replay
	if(++Timerdelay >15)
	{
		Timerdelay=0;
		wifi_command=10;	//41
	}
	break;
	case 49:
	if(++Timerdelay >8)
	{
		Timerdelay=0;
		wifi_command=50;
	}
	break;
	case 50:   //CWJAP

	NoOfdata_byte=11;
	wifi_command=51;
	Rxseqdecoder=3;
	Timerdelay=0;
	HAL_UART_Transmit_IT(&hlpuart1,CMDATCwjapRead,NoOfdata_byte);
	break;
	case 51:
	if(++Timerdelay >15)
	{
		Timerdelay=0;
		wifi_command=10; //50
	}

	break;
	case 70:   //CIPMUX

	NoOfdata_byte=13;
	wifi_command=71;
	Rxseqdecoder=4;
	Timerdelay=0;
	HAL_UART_Transmit_IT(&hlpuart1,CmdATCipmuxWrite,NoOfdata_byte);
	break;	  //2sec
	case 71:
	if(++Timerdelay >15)
	{
		Timerdelay=0;
		wifi_command=10;   //70
	}
	break;
	case 80:
	NoOfdata_byte=49;//41;
	wifi_command=81;
	Rxseqdecoder=5;
	Timerdelay=0;
	HAL_UART_Transmit_IT(&hlpuart1,CmdAtCipStartWrite,NoOfdata_byte);
	break;
	case 81:					//5sec
	if(++Timerdelay >20)
	{
		Timerdelay=0;
		wifi_command=10;
	}
	break;
	case 90:   //CIPSEND
	NoOfdata_byte	= 18;
	//lenOfURl = sprintf(PostUrl_CharFormat,"GET /isc1-lab.acceedo.in:9009/logs?mac=01&t=373&h=972&W=01&U=01&x=0\r\nHOST:usm2-ht.acceedo.in:9009\r\n\r\n");
	r_set_duration_seq1 = (Rise_Sequence1_Minute%10)+((Rise_Sequence1_Minute/10)*10)+((Rise_Sequence1_Hour%10)*100)+((Rise_Sequence1_Hour/10)*1000);
	set_duration_seq1 = (H_Timer01MinValue%10)+((H_Timer01MinValue/10)*10)+((H_Timer01HrValue%10)*100)+((H_Timer01HrValue/10)*1000);
	r_set_duration_seq2 = (Rise_Sequence2_Minute%10)+((Rise_Sequence2_Minute/10)*10)+((R_Sequence2_hour_http%10)*100)+((R_Sequence2_hour_http/10)*1000);
	set_duration_seq2 = (H_Timer02MinValue%10)+((H_Timer02MinValue/10)*10)+((H_Timer02HrValue%10)*100)+((H_Timer02HrValue/10)*1000);
	remaining_duration_seq1 =(seq1_remaining_time_min%10)+((seq1_remaining_time_min/10)*10)+((seq1_remaining_time_Hr%10)*100)+((seq1_remaining_time_Hr/10)*1000);
	remaining_duration_seq2 =(seq2_remaining_time_min%10)+((seq2_remaining_time_min/10)*10)+((seq2_remaining_time_Hr%10)*100)+((seq2_remaining_time_Hr/10)*1000);
	lenOfURl = sprintf(PostUrl_CharFormat,"GET /set_temp?u=4&p=%d&tm=%d&tl=%d&th=%d&hr=%d&"
				"h=%d&lr=%d&l=%d&hrt=%04d&ht=%04d%&lrt=%04d&lt=%04d&rv=%04d&bv=%04d&yv=%d&rc=%03d"
				"&bc=%d&yc=%d&k=%d&x=%02d\r\nHost:usm4-ht.acceedo.in:9012\r\n\r\n",
				ProcessId_Value,act_temperature_c1,act_temperature_c2,act_temperature_c3,
				Rise_Sequence1_temp,Seq1temperature,Rise_Sequence2_temp,Seq2temperature,r_set_duration_seq1,set_duration_seq1,r_set_duration_seq2,set_duration_seq2,
				remaining_duration_seq1,remaining_duration_seq2,act_temperature_c4,
				1,water_temperature,0,1,status_to_server);
	sprintf(SendData_charFormat,"AT+CIPSEND=1,%d\r\n",lenOfURl);
	memcpy(SendData_uintFormat,SendData_charFormat,NoOfdata_byte);
	HAL_UART_Transmit_IT(&hlpuart1,SendData_uintFormat,NoOfdata_byte);
	wifi_command=91;
	Rxseqdecoder=6;
	Timerdelay=0;
	HAL_UART_Transmit_IT(&hlpuart1,ESP8266TXData,NoOfdata_byte);
	break;
	case 91:
	if(++Timerdelay >15)
	{
		Timerdelay=0;
		wifi_command=10;
	}
	break;
	case 100:

		r_set_duration_seq1 = (Rise_Sequence1_Minute%10)+((Rise_Sequence1_Minute/10)*10)+((Rise_Sequence1_Hour%10)*100)+((Rise_Sequence1_Hour/10)*1000);
		set_duration_seq1 = (H_Timer01MinValue%10)+((H_Timer01MinValue/10)*10)+((H_Timer01HrValue%10)*100)+((H_Timer01HrValue/10)*1000);
		r_set_duration_seq2 = (Rise_Sequence2_Minute%10)+((Rise_Sequence2_Minute/10)*10)+((R_Sequence2_hour_http%10)*100)+((R_Sequence2_hour_http/10)*1000);
		set_duration_seq2 = (H_Timer02MinValue%10)+((H_Timer02MinValue/10)*10)+((H_Timer02HrValue%10)*100)+((H_Timer02HrValue/10)*1000);
		remaining_duration_seq1 =(seq1_remaining_time_min%10)+((seq1_remaining_time_min/10)*10)+((seq1_remaining_time_Hr%10)*100)+((seq1_remaining_time_Hr/10)*1000);
		remaining_duration_seq2 =(seq2_remaining_time_min%10)+((seq2_remaining_time_min/10)*10)+((seq2_remaining_time_Hr%10)*100)+((seq2_remaining_time_Hr/10)*1000);
	lenOfURl = sprintf(PostUrl_CharFormat,"GET /set_temp?u=4&p=%d&tm=%d&tl=%d&th=%d&hr=%d&"
						"h=%d&lr=%d&l=%d&hrt=%04d&ht=%04d%&lrt=%04d&lt=%04d&rv=%04d&bv=%04d&yv=%d&rc=%03d"
						"&bc=%d&yc=%d&k=%d&x=%02d\r\nHost:usm4-ht.acceedo.in:9012\r\n\r\n",
						ProcessId_Value,act_temperature_c1,act_temperature_c2,act_temperature_c3,
						Rise_Sequence1_temp,Seq1temperature,Rise_Sequence2_temp,Seq2temperature,r_set_duration_seq1,set_duration_seq1,r_set_duration_seq2,set_duration_seq2,
						remaining_duration_seq1,remaining_duration_seq2,act_temperature_c4,
						1,water_temperature,0,1,status_to_server);
	memcpy(PostUrl_uintFormat,PostUrl_CharFormat,lenOfURl);
	wifi_command	=	101;
	Rxseqdecoder=7;
	Timerdelay=0;

	HAL_UART_Transmit_IT(&hlpuart1,PostUrl_uintFormat,lenOfURl);
	break;
	case 101:
		if(++Timerdelay>20)
		{
			Timerdelay=0;
			wifi_command=10;
		}
	break;
	case 102:
	   if(++Timerdelay>2)
	   {
		Timerdelay=0;
		wifi_command=50;
	   }
	break;
	case 103:
	   if(++Timerdelay>2)
	   {
		Timerdelay=0;
		wifi_command=10;
	   }
	break;
	case 110:
	NoOfdata_byte=12;
	wifi_command=50;
	HAL_UART_Transmit_IT(&hlpuart1,CmdCipClose,NoOfdata_byte);
	break;
	case 120:
	break;
	default:
	wifi_command=5;
	break;
 }
}

void ESP8266::RefreshWifiData()
{
	if((RefreshBlockInfo==0)||(powercycleRefresh==1))
	{
		RefreshBlockInfo=1;
		if((currentdata==0)&&(powercycleRefresh==0))
		{
			BlockStatusOffline[sectorTosend]=0;
			W25qxx_EraseSector(601);
			W25qxx_WriteSector(BlockStatusOffline,601,0,40);
		}
		powercycleRefresh=0;
		for(j=0;j<=32;j++)
		{
			if(BlockStatusOffline[j] == 1)
			{
				sectorTosend=j;
				currentdata=0;
				break;
			}
			if(BlockStatusOffline[j] == 2)
			{
				sectorTosend=j;
				currentdata=1;
			}
		}

		sectorRead = 16*sectorTosend;
		if(W25qxx_IsEmptySector(sectorRead,0,53))
		{
			memcpy(ProductionSet_uintFormat_MEM,dummydata,54);}
		else
		{
			W25qxx_ReadSector(ProductionSet_uintFormat_MEM,sectorRead,0,53);
			if(ProductionSet_uintFormat_MEM[0] != 34 || ProductionSet_uintFormat_MEM[52] != 34)
			{
				memcpy(ProductionSet_uintFormat_MEM,dummydata,54);
			}
		}

		for(scanForUrl=1;scanForUrl<=14;scanForUrl++)
		{
			ProductionSet_uintFormat_MEM[(54*scanForUrl)-1]=',';
			if(W25qxx_IsEmptySector(sectorRead+scanForUrl,0,53))
			{
				memcpy(&ProductionSet_uintFormat_MEM[54*scanForUrl],dummydata,54);}
			else
			{
				W25qxx_ReadSector(&ProductionSet_uintFormat_MEM[54*scanForUrl],sectorRead+scanForUrl,0,53);
				if(ProductionSet_uintFormat_MEM[54*scanForUrl] != 34 || ProductionSet_uintFormat_MEM[(54*scanForUrl)+52] != 34)
				{
					memcpy(&ProductionSet_uintFormat_MEM[54*scanForUrl],dummydata,54);
				}
			}
		}

	/*	ProductionSet_uintFormat_MEM[(54*15)-1]=',';
		W25qxx_ReadSector(&ProductionSet_uintFormat_MEM[54*15],1,0,53);*///reduced due to tcp limitation

	}
}

void ESP8266::Init(void)
{
	sprintf(dummydata,"%c%02d,%04d,%04d,%03d,%03d,%02d:%02d:%02d %02d/%02d/%02d,%04d,%03d,%03d%c",'"',0,0,
				0,0,0,0,0,0,0,0,0,0,0,0,'"');
	powercycleRefresh=1;
	wifi_command=5;
	RefreshBlockInfo=0;
}
