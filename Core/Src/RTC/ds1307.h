/*
 * ds1307.h
 *
 *  Created on: Jan 28, 2023
 *      Author: MKS
 */

#ifndef SRC_RTC_DS1307_H_
#define SRC_RTC_DS1307_H_

#include "main.h"

#define addr_ds1307 (uint16_t)11010000


uint8_t bcd2bin(uint8_t data);
uint8_t bin2bcd(uint8_t data);
uint8_t rtc_read(uint8_t address);
void rtc_write(uint8_t address,uint8_t data);
void rtc_init(uint8_t rs,uint8_t sqwe,uint8_t out);
void rtc_get_time(uint8_t *hour,uint8_t *min,uint8_t *sec);
void rtc_set_time(uint8_t hour,uint8_t min,uint8_t sec);
void rtc_get_date(uint8_t *week_day, uint8_t *day,uint8_t *month,uint8_t *year);
void rtc_set_date(uint8_t week_day, uint8_t day,uint8_t month,uint8_t year);




#endif /* SRC_RTC_DS1307_H_ */
