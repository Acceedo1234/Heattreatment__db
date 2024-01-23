/*
 * GLCD.cpp
 *
 *  Created on: 15-Dec-2022
 *      Author: MKS
 */

#include "GLCD.h"
#include "main.h"
#define GLCDDELAY 10
extern TIM_HandleTypeDef htim1;
GLCD::GLCD() {
	// TODO Auto-generated constructor stub

}

GLCD::~GLCD() {
	// TODO Auto-generated destructor stub
}

void GLCD::m_ctrloff(){
	HAL_GPIO_WritePin(GPIOA,LCDRS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GLCDRW_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLCDCS1_GPIO_Port, GLCDCS1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GLCDCS2_Pin, GPIO_PIN_RESET);
}

void GLCD::m_delay(unsigned int delay){
	__HAL_TIM_SET_COUNTER(&htim1, 0);  // reset the counter
	while ((__HAL_TIM_GET_COUNTER(&htim1))<delay);  // wait for the delay to complete
}

void GLCD::m_delay(unsigned int j,uint8_t a)
{
	unsigned int i,k;
	for(i=0;i<j;i++)
 	{for(k=0;k<a;k++);
	}
}

void GLCD::m_IOWritethedata(const uint8_t finput)
{
	HAL_GPIO_WritePin(GPIOC,LCDD0_Pin,ReadtheValueAssignPinstate(0,finput));
	HAL_GPIO_WritePin(GPIOC,LCDD1_Pin,ReadtheValueAssignPinstate(1,finput));
	HAL_GPIO_WritePin(GPIOC,LCDD2_Pin,ReadtheValueAssignPinstate(2,finput));
	HAL_GPIO_WritePin(GPIOC,LCDD3_Pin,ReadtheValueAssignPinstate(3,finput));
	HAL_GPIO_WritePin(GPIOC,LCDD4_Pin,ReadtheValueAssignPinstate(4,finput));
	HAL_GPIO_WritePin(GPIOC,LCDD5_Pin,ReadtheValueAssignPinstate(5,finput));
	HAL_GPIO_WritePin(GPIOC,LCDD6_Pin,ReadtheValueAssignPinstate(6,finput));
	HAL_GPIO_WritePin(GPIOB,LCDD7_Pin, ReadtheValueAssignPinstate(7,finput));
}

void GLCD::m_displayon(){
	m_ctrloff();
	m_IOWritethedata(0x3f);
	HAL_GPIO_WritePin(GLCDCS1_GPIO_Port, GLCDCS1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC,GLCDCS2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,LCDRS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GLCDRW_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_SET);
	//m_delay(GLCDDELAY);
	m_delay(10,100);
	HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_RESET);
}

void GLCD::m_displayoff(){
	m_ctrloff();
	m_IOWritethedata(0x3e);
	HAL_GPIO_WritePin(GLCDCS1_GPIO_Port, GLCDCS1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC,GLCDCS2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,LCDRS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GLCDRW_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_SET);
	//m_delay(GLCDDELAY);
	m_delay(10,100);
	HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_RESET);
}


void GLCD::m_setcolumn(uint8_t Columvalue)
{
	uint8_t dport;
	if(Columvalue <64)
	{
		m_ctrloff();
		c=Columvalue;
		m_IOWritethedata((0x40|(Columvalue&63)));
		HAL_GPIO_WritePin(GLCDCS1_GPIO_Port, GLCDCS1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC,GLCDCS2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,LCDRS_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC,GLCDRW_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_SET);
		//m_delay(GLCDDELAY);
		m_delay(10,100);
		HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_RESET);
	}
	else
	{
		c=Columvalue;
		dport=0x40|((Columvalue-64)&63);	  //0x40 represents Column 0
		m_IOWritethedata(dport);
		HAL_GPIO_WritePin(GLCDCS1_GPIO_Port, GLCDCS1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC,GLCDCS2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,LCDRS_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC,GLCDRW_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_SET);
		//m_delay(GLCDDELAY);
		m_delay(10,100);
		HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_RESET);

	}
}

void GLCD::m_setpage(uint8_t x)
{
	uint8_t dport;
	m_ctrloff();
	dport= 0xb8|x;	   //0xb8 represents Page 0
	m_IOWritethedata(dport);
	HAL_GPIO_WritePin(GLCDCS1_GPIO_Port, GLCDCS1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC,GLCDCS2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,LCDRS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GLCDRW_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_SET);
	//m_delay(GLCDDELAY);
	m_delay(10,100);
	HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_RESET);
}

void GLCD::m_setstartline(uint8_t z)
{
	uint8_t dport;
	m_ctrloff();
	dport=0xc0|z;	   //0xc0 represents Line 0
	m_IOWritethedata(dport);
	HAL_GPIO_WritePin(GLCDCS1_GPIO_Port, GLCDCS1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC,GLCDCS2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,LCDRS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GLCDRW_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_SET);
	//m_delay(GLCDDELAY);
	m_delay(10,100);
	HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_RESET);
}

void GLCD::m_lcddata(uint8_t *value,uint16_t limit)
{
	uint16_t i;
	uint8_t dport;
	for(i=0;i<limit;i++)
	{
		if(c<64)
		{
			dport=value[i];
			m_IOWritethedata(dport);
			HAL_GPIO_WritePin(GLCDCS1_GPIO_Port, GLCDCS1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC,GLCDCS2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,LCDRS_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC,GLCDRW_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_SET);
			//m_delay(GLCDDELAY);
			m_delay(10,100);
			HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_RESET);
			c++;
		}
		else
		{
			m_setcolumn(c);
			dport=value[i];
			m_IOWritethedata(dport);
			HAL_GPIO_WritePin(GLCDCS1_GPIO_Port, GLCDCS1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC,GLCDCS2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA,LCDRS_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC,GLCDRW_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_SET);
			//m_delay(GLCDDELAY);
			m_delay(10,100);
			HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_RESET);
			c++;
		}
		if(c>127)
	           return;
	}
}

void GLCD::m_lcdputs1(uint8_t y,uint8_t x,unsigned char *str)
{
	uint8_t i;
	uint16_t a;
	m_setcolumn(y);
	m_setpage(x);
	for(i=0;str[i]!=0;i++)
	{
		a=(*(str+i));
		a*=8;
		m_lcddata(&Character8x8[a],8);
	}
}

void GLCD::m_lcdputs2(uint8_t y,uint8_t x,uint8_t *str)
{
	uint8_t i;
	uint16_t a;
	m_setcolumn(y);
	m_setpage(x);
	for(i=0;str[i]!=0;i++)
	{
		a=(*(str+i)-32);
		a*=5;
		m_lcddata(&font5x7[a],5);
	}
}

void GLCD::m_clrlcd(void)
{
    uint8_t i,j;
    for (i=0;i < 8;i++)
    {
    m_setpage(i);
    m_setcolumn(0);
        for (j= 0 ;j < 128; j++)
        	m_lcddata(&z,1);
    }
}
