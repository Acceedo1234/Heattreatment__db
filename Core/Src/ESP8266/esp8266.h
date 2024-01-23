/*
 * esp8266.h
 *
 *  Created on: Jan 21, 2023
 *      Author: MKS
 */

#ifndef SRC_ESP8266_ESP8266_H_
#define SRC_ESP8266_ESP8266_H_

#include "main.h"

/*
uint8_t Wifirefreshflag_Lpcs;
uint8_t wifi_command;
uint8_t ESP8266TXData[250];
uint8_t ContentData[250];
uint8_t OnlineData_buffer[200];
uint8_t bufferptr;
uint8_t Rxseqdecoder;
uint8_t Check_CWMODE_For_Hang;
uint8_t NoOfdata_byte;
uint8_t url_send;
uint8_t Timerdelay;
uint8_t url_buffer;
uint16_t Dyn_data_calc;
uint16_t ContentLength;
uint16_t ContentLength;
uint8_t NoOfBatch_to_Send,Framecheck;
*/
void Send_WifiCmd(void);

extern UART_HandleTypeDef hlpuart1;
#endif /* SRC_ESP8266_ESP8266_H_ */
