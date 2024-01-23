#include "main.h"
#include "font.h"
#include "font2.h"

#define true 1

extern TIM_HandleTypeDef htim1;

GPIO_PinState AssignPinstate(uint8_t position, uint8_t value);
void m_IOWriteGLCDData(unsigned char finput);
void delay_us(unsigned int delay_value);
void ctrloff(void);
void displayon(void);
void displayoff(void);
void setcolumn(unsigned char y);
void setpage(unsigned char x);

void clrlcd();
void picture(unsigned char * val);
void lcdputs1(unsigned char y,unsigned char x,unsigned char *str);
void lcdputs2(unsigned char y,unsigned char x,unsigned char *str);
void lcddata(unsigned char *value,unsigned int limit);
void setstartline(unsigned char z);

unsigned char c;
unsigned char z=0;
unsigned char dport;
void delay_us(unsigned int j)
{
	unsigned int i,k;
	for(i=0;i<j;i++)
 	{for(k=0;k<200;k++);
	}
}

//void delay_us(unsigned int delay_value)
//{
//	__HAL_TIM_SET_COUNTER(&htim1, 0);  // reset the counter
//	while ((__HAL_TIM_GET_COUNTER(&htim1))<delay_value);  // wait for the delay to complete
//}

GPIO_PinState AssignPinstate(uint8_t position, uint8_t value)
{
	GPIO_PinState pinstate;
	position = 1 << position;
	if((position & value)==true){
		pinstate = GPIO_PIN_SET;
	}
	else
	{
		pinstate = GPIO_PIN_RESET;
	}
	return(pinstate);
}


void m_IOWriteGLCDData(unsigned char finput)
{
	HAL_GPIO_WritePin(GPIOC,LCDD0_Pin,AssignPinstate(0,finput));
	HAL_GPIO_WritePin(GPIOC,LCDD1_Pin,AssignPinstate(1,finput));
	HAL_GPIO_WritePin(GPIOC,LCDD2_Pin,AssignPinstate(2,finput));
	HAL_GPIO_WritePin(GPIOC,LCDD3_Pin,AssignPinstate(3,finput));
	HAL_GPIO_WritePin(GPIOC,LCDD4_Pin,AssignPinstate(4,finput));
	HAL_GPIO_WritePin(GPIOC,LCDD5_Pin,AssignPinstate(5,finput));
	HAL_GPIO_WritePin(GPIOC,LCDD6_Pin,AssignPinstate(6,finput));
	HAL_GPIO_WritePin(GPIOB,LCDD7_Pin, AssignPinstate(7,finput));
}



void ctrloff(void)
{
	HAL_GPIO_WritePin(GPIOA,LCDRS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GLCDRW_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLCDCS1_GPIO_Port, GLCDCS1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GLCDCS2_Pin, GPIO_PIN_RESET);
}

void displayon(void)
{
	ctrloff();
	m_IOWriteGLCDData(0x3f);
	HAL_GPIO_WritePin(GLCDCS1_GPIO_Port, GLCDCS1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC,GLCDCS2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,LCDRS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GLCDRW_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_SET);
	delay_us(5);
	HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_RESET);
}

void displayoff(void)
{
	ctrloff();
	m_IOWriteGLCDData(0x3e);
	HAL_GPIO_WritePin(GLCDCS1_GPIO_Port, GLCDCS1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC,GLCDCS2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,LCDRS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GLCDRW_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_SET);
	delay_us(5);
	HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_RESET);
}

void setcolumn(unsigned char y)
{
	if(y<64)
	{
		ctrloff();
		c=y;
		m_IOWriteGLCDData(0x40|(y&63));
		HAL_GPIO_WritePin(GLCDCS1_GPIO_Port, GLCDCS1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC,GLCDCS2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,LCDRS_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC,GLCDRW_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_SET);
		delay_us(5);
		HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_RESET);
	}
	else
	{
		c=y;
		dport=0x40|((y-64)&63);	  //0x40 represents Column 0
		m_IOWriteGLCDData(dport);
		HAL_GPIO_WritePin(GLCDCS1_GPIO_Port, GLCDCS1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC,GLCDCS2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,LCDRS_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC,GLCDRW_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_SET);
		delay_us(5);
		HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_RESET);

	}
}

void setpage(unsigned char x)
{
	ctrloff();
	dport= 0xb8|x;	   //0xb8 represents Page 0
	m_IOWriteGLCDData(dport);
	HAL_GPIO_WritePin(GLCDCS1_GPIO_Port, GLCDCS1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC,GLCDCS2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,LCDRS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GLCDRW_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_SET);
	delay_us(5);
	HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_RESET);
}

//Function to Scroll Strings
void setstartline(unsigned char z)
{
	ctrloff();
	dport=0xc0|z;	   //0xc0 represents Line 0
	m_IOWriteGLCDData(dport);
	HAL_GPIO_WritePin(GLCDCS1_GPIO_Port, GLCDCS1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC,GLCDCS2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,LCDRS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GLCDRW_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_SET);
	delay_us(5);
	HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_RESET);
}

void lcddata(unsigned char *value,unsigned int limit)
{
	unsigned int i;
	for(i=0;i<limit;i++)
	{
		if(c<64)
		{
			dport=value[i];
			m_IOWriteGLCDData(dport);
			HAL_GPIO_WritePin(GLCDCS1_GPIO_Port, GLCDCS1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC,GLCDCS2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,LCDRS_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC,GLCDRW_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_SET);
			delay_us(5);
			HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_RESET);
			c++;
		}
		else
		{
			setcolumn(c);
			dport=value[i];
			m_IOWriteGLCDData(dport);
			HAL_GPIO_WritePin(GLCDCS1_GPIO_Port, GLCDCS1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC,GLCDCS2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA,LCDRS_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC,GLCDRW_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_SET);
			delay_us(5);
			HAL_GPIO_WritePin(GPIOC,GLCDEN_Pin, GPIO_PIN_RESET);
			c++;
		}
		if(c>127)
	           return;
	}
}

void lcdputs1(unsigned char y,unsigned char x,unsigned char *str)
{
	unsigned char i;
	unsigned int a;
	setcolumn(y);
	setpage(x);
	for(i=0;str[i]!=0;i++)
	{
		a=(*(str+i));
		a*=8;
		lcddata(&Character8x8[a],8);
	}
}


void lcdputs2(unsigned char y,unsigned char x,unsigned char *str)
{
	unsigned char i;
	unsigned int a;
	setcolumn(y);
	setpage(x);
	for(i=0;str[i]!=0;i++)
	{
		a=(*(str+i)-32);
		a*=5;
		lcddata(&font5x7[a],5);
	}
}

//Function to display Image
void picture(unsigned char * val)
{
	unsigned char j;
	setcolumn(0);
	setpage(0);
	for (j=0;j<8;j++)
	{
		setpage(j);
		setcolumn(0);
		lcddata(&val[(j*128)],128);
	}
}

void clrlcd()
{
    unsigned char i,j;
    for (i=0;i < 8;i++)
    {
	setpage(i);
	setcolumn(0);
        for (j= 0 ;j < 128; j++)
        lcddata(&z,1);
    }
}

