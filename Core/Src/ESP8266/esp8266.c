/*
 * esp8266.c
 *
 *  Created on: Jan 21, 2023
 *      Author: MKS
 */
#include "esp8266.h"
#if 0
void Send_WifiCmd(void)
{
	unsigned char i;
	unsigned int x,y;
	static unsigned int ContentLength;

	switch(wifi_command)
 	{
 	case 5:
 		HAL_GPIO_WritePin(GPIOB, WIFIRST_Pin, GPIO_PIN_SET);
		HAL_Delay(1000);
		HAL_GPIO_WritePin(GPIOB, WIFIRST_Pin, GPIO_PIN_RESET);
		wifi_command=13;

	break;
 	case 10://reset
	ESP8266TXData[0] = 'A';
	ESP8266TXData[1] = 'T';
	ESP8266TXData[2] = '+';
	ESP8266TXData[3] = 'R';
	ESP8266TXData[4] = 'S';
	ESP8266TXData[5] = 'T';
	ESP8266TXData[6] = 0x0d;
	ESP8266TXData[7] = 0x0a;
	NoOfdata_byte=7;
	wifi_command=13;
	Timerdelay=0;
	bufferptr=0;
	HAL_UART_Transmit_IT(&hlpuart1,ESP8266TXData,NoOfdata_byte);
	break;
	case 11:
	if(++Timerdelay >6)
	{
		Timerdelay=0;
		wifi_command=14;
	}
	break;
	case 12:
	ESP8266TXData[0] = 'A';
	ESP8266TXData[1] = 'T';
	ESP8266TXData[2] = 'E';
	ESP8266TXData[3] = '0';
	ESP8266TXData[4] = 0x0d;
	ESP8266TXData[5] = 0x0a;
	NoOfdata_byte=6;
	wifi_command=13;
	Timerdelay=0;
	HAL_UART_Transmit_IT(&hlpuart1,ESP8266TXData,NoOfdata_byte);
	break;
	case 13:
	if(++Timerdelay >15)
	{
		Timerdelay=0;
		wifi_command=20;
	}
	break;
	case 14:
	ESP8266TXData[0] = 'A';
	ESP8266TXData[1] = 'T';
	ESP8266TXData[2] = 0x0d;
	ESP8266TXData[3] = 0x0a;
	NoOfdata_byte=4;
	Rxseqdecoder=8;
	wifi_command=20;//default wait 30sec
	Timerdelay=0;
	HAL_UART_Transmit_IT(&hlpuart1,ESP8266TXData,NoOfdata_byte);
	break;
	case 15:
	if(++Timerdelay >2)
	{
		Timerdelay=0;
	}
	break;
	case 20:   //CWMODE		//hardrest sequce//1.0 for wifi reset
	ESP8266TXData[0] = 'A';
	ESP8266TXData[1] = 'T';
	ESP8266TXData[2] = '+';
	ESP8266TXData[3] = 'C';
	ESP8266TXData[4] = 'W';
	ESP8266TXData[5] = 'M';
	ESP8266TXData[6] = 'O';
	ESP8266TXData[7] = 'D';
	ESP8266TXData[8] = 'E';
	ESP8266TXData[9] = '=';
	ESP8266TXData[10] = '1';
	ESP8266TXData[11] = 0x0d;
	ESP8266TXData[12] = 0x0a;
	NoOfdata_byte=13;
	Rxseqdecoder=1;	  //add retry
	Timerdelay=0;
	bufferptr=0;
	HAL_UART_Transmit_IT(&hlpuart1,ESP8266TXData,NoOfdata_byte);
	Check_CWMODE_For_Hang = Check_CWMODE_For_Hang+1;
	wifi_command=21;

	break;
	case 21:	//waiting for Ok  && if above 30 seconds resend command
	if(++Timerdelay >5)
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
	ESP8266TXData[0] = 'A';
	ESP8266TXData[1] = 'T';
	ESP8266TXData[2] = '+';
	ESP8266TXData[3] = 'C';
	ESP8266TXData[4] = 'W';
	ESP8266TXData[5] = 'J';
	ESP8266TXData[6] = 'A';
	ESP8266TXData[7] = 'P';
	ESP8266TXData[8] = '=';
	ESP8266TXData[9] = '"';
	ESP8266TXData[10] = 'T';
	ESP8266TXData[11] = 'P';
	ESP8266TXData[12] = '-';
	ESP8266TXData[13] = 'L';
	ESP8266TXData[14] = 'I';
	ESP8266TXData[15] = 'N';
	ESP8266TXData[16] = 'K';
	ESP8266TXData[17] = '_';
	ESP8266TXData[18] = 'A';
	ESP8266TXData[19] = 'C';
	ESP8266TXData[20] = 'C';
	ESP8266TXData[21] = 'E';
	ESP8266TXData[22] = 'E';
	ESP8266TXData[23] = 'D';
	ESP8266TXData[24] = '"';
	ESP8266TXData[25] = ',';
	ESP8266TXData[26] = '"';
	ESP8266TXData[27] = '9';//(unsigned char)(((WifiUserId%10000)/1000)+0x30);	4259241555
	ESP8266TXData[28] = '9';//(unsigned char)(((WifiUserId%1000)/100)+0x30);//'e';
	ESP8266TXData[29] = '9';//(unsigned char)(((WifiUserId%100)/10)+0x30);//'s';
	ESP8266TXData[30] = '4';//(unsigned char)((WifiUserId%10)+0x30);//'h';
	ESP8266TXData[31] = '1';//(unsigned char)(((WifiUserId2%10000)/1000)+0x30);
	ESP8266TXData[32] = '1';//(unsigned char)(((WifiUserId2%1000)/100)+0x30);//'e';
	ESP8266TXData[33] = '1';//(unsigned char)(((WifiUserId2%100)/10)+0x30);//'s';
	ESP8266TXData[34] = '2';//(unsigned char)(((WifiUserId%10000)/1000)+0x30);
	ESP8266TXData[35] = '"';
	ESP8266TXData[36] = 0x0d;
	ESP8266TXData[37] = 0x0a;
	NoOfdata_byte=38;//32;
	Rxseqdecoder=2;
	wifi_command=41;
	Timerdelay=0;
	HAL_UART_Transmit_IT(&hlpuart1,ESP8266TXData,NoOfdata_byte);
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
	ESP8266TXData[0] = 'A';
	ESP8266TXData[1] = 'T';
	ESP8266TXData[2] = '+';
	ESP8266TXData[3] = 'C';
	ESP8266TXData[4] = 'W';
	ESP8266TXData[5] = 'J';
	ESP8266TXData[6] = 'A';
	ESP8266TXData[7] = 'P';
	ESP8266TXData[8] = '?';
	ESP8266TXData[9] = 0x0d;
	ESP8266TXData[10] = 0x0a;
	NoOfdata_byte=11;
	wifi_command=51;
	Rxseqdecoder=3;
	Timerdelay=0;
	HAL_UART_Transmit_IT(&hlpuart1,ESP8266TXData,NoOfdata_byte);
	break;
	case 51:
	if(++Timerdelay >15)
	{
		Timerdelay=0;
		wifi_command=10; //50
	}

	break;
	case 70:   //CIPMUX
	ESP8266TXData[0] = 'A';
	ESP8266TXData[1] = 'T';
	ESP8266TXData[2] = '+';
	ESP8266TXData[3] = 'C';
	ESP8266TXData[4] = 'I';
	ESP8266TXData[5] = 'P';
	ESP8266TXData[6] = 'M';
	ESP8266TXData[7] = 'U';
	ESP8266TXData[8] = 'X';
	ESP8266TXData[9] = '=';
	ESP8266TXData[10] = '0';
	ESP8266TXData[11] = 0x0d;
	ESP8266TXData[12] = 0x0a;
	NoOfdata_byte=13;
	wifi_command=71;
	Rxseqdecoder=4;
	Timerdelay=0;
	HAL_UART_Transmit_IT(&hlpuart1,ESP8266TXData,NoOfdata_byte);
	break;	  //2sec
	case 71:
	if(++Timerdelay >15)
	{
		Timerdelay=0;
		wifi_command=10;   //70
	}
	break;
	case 80:
	ESP8266TXData[0] = 'A';
	ESP8266TXData[1] = 'T';
	ESP8266TXData[2] = '+';
	ESP8266TXData[3] = 'C';
	ESP8266TXData[4] = 'I';
	ESP8266TXData[5] = 'P';
	ESP8266TXData[6] = 'S';
	ESP8266TXData[7] = 'T';
	ESP8266TXData[8] = 'A';
	ESP8266TXData[9] = 'R';
	ESP8266TXData[10] = 'T';
	ESP8266TXData[11] = '=';
	ESP8266TXData[12] = '"';
	ESP8266TXData[13] = 'T';
	ESP8266TXData[14] = 'C';
	ESP8266TXData[15] = 'P';
	ESP8266TXData[16] = '"';
	ESP8266TXData[17] = ',';
	ESP8266TXData[18] = '"';
	ESP8266TXData[19] = 'l';	//ESP8266TXData[19] = '5';
	ESP8266TXData[20] = 'p';	//ESP8266TXData[20] = '2';
	ESP8266TXData[21] = 'd';	//ESP8266TXData[21] = '.';
	ESP8266TXData[22] = 'c';	//ESP8266TXData[22] = '1';
	ESP8266TXData[23] = '-';	//ESP8266TXData[23] = '8';
	ESP8266TXData[24] = 'u';	//ESP8266TXData[24] = '4';
	ESP8266TXData[25] = 's';	//ESP8266TXData[25] = '.';
	ESP8266TXData[26] = 'm';	//ESP8266TXData[26] = '4';
 	ESP8266TXData[27] = '3';	//ESP8266TXData[27] = '9';
	ESP8266TXData[28] = '.';	//ESP8266TXData[28] = '.';
	ESP8266TXData[29] = 'a';	//ESP8266TXData[29] = '2';
	ESP8266TXData[30] = 'c';	//ESP8266TXData[30] = '5';
	ESP8266TXData[31] = 'c';	//ESP8266TXData[31] = '5';
	ESP8266TXData[32] = 'e';	//ESP8266TXData[32] = '"';
	ESP8266TXData[33] = 'e';
	ESP8266TXData[34] = 'd';
	ESP8266TXData[35] = 'o';
	ESP8266TXData[36] = '.';
	ESP8266TXData[37] = 'i';
	ESP8266TXData[38] = 'n';
	ESP8266TXData[39] = '"';
	ESP8266TXData[40] = ',';
	ESP8266TXData[41] = '9';
	ESP8266TXData[42] = '0';
	ESP8266TXData[43] = '0';
	ESP8266TXData[44] = '9';
	ESP8266TXData[45] = 0x0d;
	ESP8266TXData[46] = 0x0a;
	NoOfdata_byte=47;//41;
	wifi_command=81;
	Rxseqdecoder=5;
	Timerdelay=0;
	HAL_UART_Transmit_IT(&hlpuart1,ESP8266TXData,NoOfdata_byte);
	break;
	case 81:					//5sec
	if(++Timerdelay >20)
	{
		Timerdelay=0;
		wifi_command=10;
	}
	break;
	case 90:   //CIPSEND
/*	if(Sl_no>=Sl_no_K1){
		Current_table_point		=  Sl_no-Sl_no_K1;
	}
	else
	{
	  Current_table_point=0;
	}
	Pendingdata_to_send 	=  Sl_no_K1;
	if(MaxLimitReached==1){
		if(MAX_STORAGE ==  Sl_no_K1){
			 Send_Dummy_Frame		= 0;
			 NoOfBatch_to_Send      = 1;
		}
		else{
			NoOfBatch_to_Send		= (MAX_STORAGE-Sl_no_K1)+1;
			Send_Dummy_Frame		= 0;
		}
	}
	else if(Current_table_point==0){
	   NoOfBatch_to_Send=1;
	   Send_Dummy_Frame= 1;
	}
	else
	{
	   NoOfBatch_to_Send		= Current_table_point;
	   Send_Dummy_Frame= 0;
	}
	if(MaxLimitReached == 1){
	//	 Sl_no_K1				= 0;
	UpdateRefresh_MaxLmt = 1;
	}
	else{
		Sl_no_to_send 				= Sl_no;
	}*/
	//ContentLength = (58*NoOfBatch_to_Send)+1+(NoOfBatch_to_Send);
	NoOfBatch_to_Send=1;
	ContentLength = (60*NoOfBatch_to_Send)-(NoOfBatch_to_Send-1);
	Dyn_data_calc = 151+(ContentLength);
	Framecheck=0;
	ESP8266TXData[0] = 'A';
	ESP8266TXData[1] = 'T';
	ESP8266TXData[2] = '+';
	ESP8266TXData[3] = 'C';
	ESP8266TXData[4] = 'I';
	ESP8266TXData[5] = 'P';
	ESP8266TXData[6] = 'S';
	ESP8266TXData[7] = 'E';
	ESP8266TXData[8] = 'N';
	ESP8266TXData[9] = 'D';
	ESP8266TXData[10] = '=';
	ESP8266TXData[11] = (unsigned char)(((Dyn_data_calc%10000)/1000)+0x30);
 	ESP8266TXData[12] = (unsigned char)(((Dyn_data_calc%1000)/100)+0x30);	  //url_send	ESP8266TXData[13] = '2';
	ESP8266TXData[13] = (unsigned char)(((Dyn_data_calc%100)/10)+0x30);	//	ESP8266TXData[14] = '0';
	ESP8266TXData[14] = (unsigned char)((Dyn_data_calc%10)+0x30);		//	ESP8266TXData[15] = '3';	//179-178  //194
	ESP8266TXData[15] = 0x0d;
	ESP8266TXData[16] = 0x0a;
	NoOfdata_byte	= 17;
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

	url_buffer =0;
   	ESP8266TXData[url_buffer] = 'P';
    url_buffer++;
	ESP8266TXData[url_buffer] = 'O';
    url_buffer++;
	ESP8266TXData[url_buffer] = 'S';
    url_buffer++;
	ESP8266TXData[url_buffer] = 'T';
    url_buffer++;
	ESP8266TXData[url_buffer] = ' ';
    url_buffer++;
	ESP8266TXData[url_buffer] = '/';
    url_buffer++;
	ESP8266TXData[url_buffer] = 'p';
    url_buffer++;
	ESP8266TXData[url_buffer] = 'r';
    url_buffer++;
	ESP8266TXData[url_buffer] = 'o';
    url_buffer++;
	ESP8266TXData[url_buffer] = 'd';
    url_buffer++;
	ESP8266TXData[url_buffer] = 'u';
    url_buffer++;
	ESP8266TXData[url_buffer] = 'c';
    url_buffer++;
	ESP8266TXData[url_buffer] = 't';
    url_buffer++;
	ESP8266TXData[url_buffer] = 'i';
    url_buffer++;
	ESP8266TXData[url_buffer] = 'o';
    url_buffer++;
	ESP8266TXData[url_buffer] = 'n';
    url_buffer++;
	ESP8266TXData[url_buffer] = 'C';
    url_buffer++;
	ESP8266TXData[url_buffer] = 'o';
    url_buffer++;
	ESP8266TXData[url_buffer] = 'u';
    url_buffer++;
	ESP8266TXData[url_buffer] = 'n';
    url_buffer++;
	ESP8266TXData[url_buffer] = 't';
    url_buffer++;
	ESP8266TXData[url_buffer] = 'P';
    url_buffer++;
	ESP8266TXData[url_buffer] = 'o';
    url_buffer++;
	ESP8266TXData[url_buffer] = 's';
    url_buffer++;
	ESP8266TXData[url_buffer] = 't';
    url_buffer++;
	ESP8266TXData[url_buffer] = '?';
    url_buffer++;
	ESP8266TXData[url_buffer] = 'm';
    url_buffer++;
	ESP8266TXData[url_buffer] = 'a';
    url_buffer++;
	ESP8266TXData[url_buffer] = 'c';
    url_buffer++;
	ESP8266TXData[url_buffer] = '=';
    url_buffer++;
	ESP8266TXData[url_buffer] = (unsigned char)(((0%100)/10)+0x30);//MachineId(Tuneable)
    url_buffer++;
	ESP8266TXData[url_buffer] = (unsigned char)((4%10)+0x30);
    url_buffer++;
	ESP8266TXData[url_buffer] =  ' ';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'H';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'T';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'T';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'P';
    url_buffer++;
	ESP8266TXData[url_buffer] =  '/';
    url_buffer++;
	ESP8266TXData[url_buffer] =  '1';
    url_buffer++;
	ESP8266TXData[url_buffer] =  '.';
    url_buffer++;
	ESP8266TXData[url_buffer] =  '1';
    url_buffer++;
	ESP8266TXData[url_buffer] =  0x0d;
    url_buffer++;
	ESP8266TXData[url_buffer] =  0x0a;
    url_buffer++;
	ESP8266TXData[url_buffer] =  'H';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'o';
    url_buffer++;
	ESP8266TXData[url_buffer] =  's';
    url_buffer++;
	ESP8266TXData[url_buffer] =  't';
    url_buffer++;
	ESP8266TXData[url_buffer] =  ':';
    url_buffer++;
	ESP8266TXData[url_buffer] =  ' ';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'l';	   //5
    url_buffer++;
	ESP8266TXData[url_buffer] =  'p';	   //2
    url_buffer++;
	ESP8266TXData[url_buffer] =  'd';	   //.
    url_buffer++;
	ESP8266TXData[url_buffer] =  'c';	   //1
    url_buffer++;
	ESP8266TXData[url_buffer] =  '-';	   //8
    url_buffer++;
	ESP8266TXData[url_buffer] =  'u';	   //4
    url_buffer++;
	ESP8266TXData[url_buffer] =  's';	   //.
    url_buffer++;
	ESP8266TXData[url_buffer] =  'm';	   //4
    url_buffer++;
	ESP8266TXData[url_buffer] =  '3';	   //9
    url_buffer++;
	ESP8266TXData[url_buffer] =  '.';	   //.
    url_buffer++;
	ESP8266TXData[url_buffer] =  'a';	   //2
    url_buffer++;
	ESP8266TXData[url_buffer] =  'c';	   //5
    url_buffer++;
	ESP8266TXData[url_buffer] =  'c';	   //5
    url_buffer++;
	ESP8266TXData[url_buffer] =  'e';	   //:
    url_buffer++;
	ESP8266TXData[url_buffer] =  'e';	   //9
    url_buffer++;
	ESP8266TXData[url_buffer] =  'd';	   //0
    url_buffer++;
	ESP8266TXData[url_buffer] =  'o';	   //0
    url_buffer++;
	ESP8266TXData[url_buffer] =  '.';	   //9
    url_buffer++;
	ESP8266TXData[url_buffer] =  'i';	   //
    url_buffer++;
	ESP8266TXData[url_buffer] =  'n';	   //
    url_buffer++;
	ESP8266TXData[url_buffer] =  ':';	   //
    url_buffer++;
	ESP8266TXData[url_buffer] =  '9';	   //
    url_buffer++;
	ESP8266TXData[url_buffer] =  '0';	   //
    url_buffer++;
	ESP8266TXData[url_buffer] =  '0';	   //
    url_buffer++;
	ESP8266TXData[url_buffer] =  '9';	   //
    url_buffer++;
	ESP8266TXData[url_buffer] =  0x0d;
    url_buffer++;
	ESP8266TXData[url_buffer] =  0x0a;
    url_buffer++;
	ESP8266TXData[url_buffer] =  'A';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'c';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'c';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'e';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'p';
    url_buffer++;
	ESP8266TXData[url_buffer] =  't';
    url_buffer++;
	ESP8266TXData[url_buffer] =  ':';
    url_buffer++;
	ESP8266TXData[url_buffer] =  ' ';
    url_buffer++;
	ESP8266TXData[url_buffer] =  't';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'e';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'x';
    url_buffer++;
	ESP8266TXData[url_buffer] =  't';
    url_buffer++;
	ESP8266TXData[url_buffer] =  '/';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'h';
    url_buffer++;
	ESP8266TXData[url_buffer] =  't';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'm';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'l';
    url_buffer++;
	ESP8266TXData[url_buffer] =  0x0d;
    url_buffer++;
	ESP8266TXData[url_buffer] =  0x0a;
    url_buffer++;
	ESP8266TXData[url_buffer] =  'C';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'o';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'n';
    url_buffer++;
	ESP8266TXData[url_buffer] =  't';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'e';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'n';
    url_buffer++;
	ESP8266TXData[url_buffer] =  't';
    url_buffer++;
	ESP8266TXData[url_buffer] =  '-';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'T';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'y';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'p';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'e';
    url_buffer++;
	ESP8266TXData[url_buffer] =  ':';
    url_buffer++;
	ESP8266TXData[url_buffer] =  ' ';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'a';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'p';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'p';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'l';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'i';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'c';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'a';
    url_buffer++;
	ESP8266TXData[url_buffer] =  't';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'i';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'o';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'n';
    url_buffer++;
	ESP8266TXData[url_buffer] =  '/';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'j';
    url_buffer++;
	ESP8266TXData[url_buffer] =  's';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'o';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'n';
    url_buffer++;
	ESP8266TXData[url_buffer] =  0x0d;
    url_buffer++;
	ESP8266TXData[url_buffer] =  0x0a;
     url_buffer++;
	ESP8266TXData[url_buffer] =  'C';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'o';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'n';
    url_buffer++;
	ESP8266TXData[url_buffer] =  't';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'e';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'n';
    url_buffer++;
	ESP8266TXData[url_buffer] =  't';
    url_buffer++;
	ESP8266TXData[url_buffer] =  '-';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'L';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'e';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'n';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'g';
    url_buffer++;
	ESP8266TXData[url_buffer] =  't';
    url_buffer++;
	ESP8266TXData[url_buffer] =  'h';
	url_buffer++;
	ESP8266TXData[url_buffer] =  ':';
	url_buffer++;
	ESP8266TXData[url_buffer] =  ' ';
	url_buffer++;
	ESP8266TXData[url_buffer] =  (unsigned char)(((ContentLength%10000)/1000)+0x30);
    url_buffer++;
	ESP8266TXData[url_buffer] =  (unsigned char)(((ContentLength%1000)/100)+0x30);
    url_buffer++;
	ESP8266TXData[url_buffer] =  (unsigned char)(((ContentLength%100)/10)+0x30);
    url_buffer++;
	ESP8266TXData[url_buffer] =  (unsigned char)((ContentLength%10)+0x30);;
	url_buffer++;
	ESP8266TXData[url_buffer] =  0x0d;
    url_buffer++;
	ESP8266TXData[url_buffer] =  0x0a;
    url_buffer++;
	ESP8266TXData[url_buffer] =  0x0d;
    url_buffer++;
	ESP8266TXData[url_buffer] =  0x0a;
    url_buffer++;
	ESP8266TXData[url_buffer] =  '[';
    url_buffer++;
	NoOfdata_byte	= 	url_buffer;
		wifi_command	=	101;


	NoOfdata_byte	= url_buffer;
	wifi_command=101;
	Timerdelay=0;

	HAL_UART_Transmit_IT(&hlpuart1,ESP8266TXData,url_buffer);
	break;
	case 101:
	url_buffer=0;
	Framecheck =  Framecheck+1;
	OnlineData_buffer[url_buffer] =  '"';
    url_buffer++;
	OnlineData_buffer[url_buffer] = (unsigned char)(1);
	url_buffer++;
	OnlineData_buffer[url_buffer] =  ',';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  ',';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  ',';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  ','; //MaxLimitReached
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  ',';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  ',';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  ':';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  ':';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  ' ';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  '/';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  '/';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  ',';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  ',';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  ',';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 1;
	url_buffer++;
	OnlineData_buffer[url_buffer] =2;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  '""';
	url_buffer++;
	NoOfBatch_to_Send=NoOfBatch_to_Send-1;

	if(NoOfBatch_to_Send!=0){OnlineData_buffer[url_buffer] =  ',';
	url_buffer++; }
	HAL_UART_Transmit_IT(&hlpuart1,OnlineData_buffer,url_buffer);
	wifi_command=104;
	if(NoOfBatch_to_Send==0){wifi_command=104;}
	else{wifi_command=101;}
	break;
	case 106:
	url_buffer=0;
	Framecheck =  Framecheck+1;
	OnlineData_buffer[url_buffer] =  '"';
    url_buffer++;
	OnlineData_buffer[url_buffer] = (unsigned char)((0)+0x30);
	url_buffer++;
	OnlineData_buffer[url_buffer] =  ',';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  ',';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  ',';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] =0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  ',';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] =0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] =0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  ',';
	url_buffer++;
	OnlineData_buffer[url_buffer] =0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  ',';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  ':';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  ':';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  ' ';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  '/';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  '/';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  ',';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  ',';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] =0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  ',';
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
	url_buffer++;
	OnlineData_buffer[url_buffer] = 0;
    url_buffer++;
	OnlineData_buffer[url_buffer] =  '""';
	url_buffer++;
	NoOfBatch_to_Send=0;
	if(NoOfBatch_to_Send!=0){OnlineData_buffer[url_buffer] =  ',';
	url_buffer++; }
	HAL_UART_Transmit_IT(&hlpuart1,OnlineData_buffer,url_buffer);
	wifi_command=104;
	break;
	case 104:
		url_buffer=0;
		OnlineData_buffer[url_buffer] =  ']';
		url_buffer++;
		HAL_UART_Transmit_IT(&hlpuart1,OnlineData_buffer,url_buffer);
		Rxseqdecoder=7;
		wifi_command=105;
	break;
	case 105:
		if(++Timerdelay>40)
	   {
	   	Timerdelay=0;
		wifi_command=10;
	   }
	break;
	case 102:

	   if(++Timerdelay>10)
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
	ESP8266TXData[0] = 'A';
	ESP8266TXData[1] = 'T';
	ESP8266TXData[2] = '+';
	ESP8266TXData[3] = 'C';
	ESP8266TXData[4] = 'I';
	ESP8266TXData[5] = 'P';
	ESP8266TXData[6] = 'C';
	ESP8266TXData[7] = 'L';
	ESP8266TXData[8] = 'O';
	ESP8266TXData[9] = 'S';
	ESP8266TXData[10] = 'E';
	ESP8266TXData[11] = 0x0a;
	ESP8266TXData[12] = 0x0d;
	NoOfdata_byte=12;
	wifi_command=50;
	HAL_UART_Transmit_IT(&hlpuart1,ESP8266TXData,NoOfdata_byte);
	break;
	case 120:
	break;
	default:
	wifi_command=5;
	break;
 }
}
#endif
