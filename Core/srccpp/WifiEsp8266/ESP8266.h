/*
 * ESP8266.h
 *
 *  Created on: 09-Feb-2023
 *      Author: MKS
 */

#ifndef SRCCPP_WIFIESP8266_ESP8266_H_
#define SRCCPP_WIFIESP8266_ESP8266_H_

class ESP8266 {
public:
	ESP8266();
	virtual ~ESP8266();
	void run();
	void Init(void);
private:
	void Send_WifiCmd(void);
	void RefreshWifiData(void);


	uint8_t i;
	uint16_t x,y;
	uint8_t j;
	uint16_t ContentLength;

	uint8_t CMDAtRst[9]="AT+RST\r\n";
	uint8_t CMDAtEch0[7]="ATE0\r\n";
	uint8_t CMDATok[6] = "AT\r\n";
	uint8_t CMDATCWMODE[15]="AT+CWMODE=3\r\n";
	uint8_t CMDATCWJAPUsernamePswB1[10] = {'A','T','+','C','W','J','A','P','=','"'};
	uint8_t CMDATCWJAPUsernamePswB2[3] = {'"',',','"'};
	uint8_t CMDATCWJAPUsernamePswB3[3] = {'"','\r','\n'};
	uint8_t CMDATCWJAPUsernamePsw[45] = {'A','T','+','C','W','J','A','P','=','"','A','C','C',
										'E','E','D','O','_','E','D','I','M','A','X','"',',','"',
										'A','C','C','E','E','D','O','@','1','2','3','"','\r','\n'};
	uint8_t CMDATCwjapRead[13]="AT+CWJAP?\r\n";
	uint8_t CmdATCipmuxWrite[15]="AT+CIPMUX=1\r\n";
	uint8_t CmdAtCipStartWrite[50]= {'A','T','+','C','I','P','S','T','A','R','T',
			'=','1',',','"','T','C','P','"',',','"','u','s','m','4','-','h','t','.',
			'a','c','c','e','e','d','o','.','i','n','"',',','9','0','1','2','\r','\n'};
	uint8_t SendData_uintFormat[20];
	char SendData_charFormat[20]={0};
	char PostUrl_CharFormat[220];
	uint8_t PostUrl_uintFormat[220];
	uint8_t CmdCipClose[15]="AT+CIPCLOSE\r\n";

	uint16_t contentLengthRef;
	uint16_t sectorRead;
	uint8_t SectorStatus;
	uint8_t scanForUrl;

	uint8_t sectorTosend;
	uint8_t currentdata;


	char dummydata[54] ;//= {"00,0000,0000,000,000,00:00:00 00/00/00,0000,000,000"};
};

/*Client to server exchange*/
extern uint16_t act_temperature_c1,act_temperature_c2,act_temperature_c3,act_temperature_c4;
extern uint16_t Seq1temperature;
extern uint16_t Seq2temperature;
extern uint8_t Seq1durationHr,Seq1durationMin,Seq2durationHr,Seq2durationMin;
extern uint8_t seq1_remaining_time_Hr,seq1_remaining_time_min,seq2_remaining_time_Hr,seq2_remaining_time_min;
extern uint8_t status_to_server;
extern uint16_t ProcessId_Value;



#endif /* SRCCPP_WIFIESP8266_ESP8266_H_ */
