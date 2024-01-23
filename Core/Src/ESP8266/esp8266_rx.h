/*
 * esp8266_rx.h
 *
 *  Created on: Jan 21, 2023
 *      Author: MKS
 */

#ifndef SRC_ESP8266_ESP8266_RX_H_
#define SRC_ESP8266_ESP8266_RX_H_

#include"main.h"


void ESPRxDecoder(unsigned char Rxwifi_data,unsigned char Rxseqdecoder);
uint8_t DecToASCIIFun(unsigned char TempVar);
void ESPRXDataSeg(void);

uint8_t Uart_rx_buffer[70];
uint8_t Data_bufferptr;
uint8_t Err_bufferptr;
uint8_t WifiDisplay;
uint8_t Error_Close;
uint8_t Updatetimeinfo;

extern uint8_t bufferptr;
extern uint8_t Check_CWMODE_For_Hang;

extern uint8_t wifi_command;

uint8_t RxCompleteU2C1WIFI;
uint8_t Valid_DataWifi1;


#endif /* SRC_ESP8266_ESP8266_RX_H_ */
