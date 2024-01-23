/*
 * W5500.cpp
 *
 *  Created on: 23-Dec-2022
 *      Author: MKS
 */

#include "W5500.h"
//#if defined(W5500_ETHERNET_SHIELD)

// W5500 controller instance
W5500Class w5500;

// SPI details
//SPISettings wiznet_SPI_settings(8000000, MSBFIRST, SPI_MODE0);
uint8_t SPI_CS;


W5500Class::W5500Class() {
	// TODO Auto-generated constructor stub

}

W5500Class::~W5500Class() {
	// TODO Auto-generated destructor stub
}

//void W5500Class::init(uint8_t ss_pin)
//{
//  SPI_CS = ss_pin;
//
//  delay(1000);
//  initSS();
//  SPI.begin();
//  w5500.swReset();
//  for (int i=0; i<MAX_SOCK_NUM; i++) {
//    uint8_t cntl_byte = (0x0C + (i<<5));
//    write( 0x1E, cntl_byte, 2); //0x1E - Sn_RXBUF_SIZE
//    write( 0x1F, cntl_byte, 2); //0x1F - Sn_TXBUF_SIZE
//  }
//}

