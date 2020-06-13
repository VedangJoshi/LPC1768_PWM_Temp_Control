/*
 * Fan_Curve_Table.h
 *
 *  Created on: Jun 12, 2020
 *      Author: Vedang Joshi
 */

#ifndef FAN_CURVE_TABLE_H_
#define FAN_CURVE_TABLE_H_

#include "mbed.h"
#include "TextLCD.h"
#include "IAP.h"

#define CONFIG 0x01
#define BIT_RES_12 0x60
#define MODE_4HZ 0xA0
#define TABLE_SIZE 6
#define	MEM_SIZE 4096
#define TARGET_SECTOR 29

const float sensistivity = 0.0625;
const int addr = 0x90;
char config[3];
char temp_read[2];
char config_reg[3];
float temp;
unsigned int pwm_period_us = 10000;

IAP iap;
I2C TMP102(p9, p10);
TextLCD lcd(p17, p16, p12, p13, p14, p15);
Ticker read_temp;

PwmOut pwm_ctl(p22);
Serial pc(USBTX, USBRX);

void temperature();
void store_fan_curve_table();

struct fan_curve_table_element {
	float temp;
	float pwm_factor;
};

struct fan_curve_table_element fan_curve_table[TABLE_SIZE] =
		{ { 10.0, 0.0 }, { 20.0, 0.4 }, { 25.0, 0.6 }, { 30.0, 0.7 }, { 35.0,
				0.8 }, { 45.0, 1.0 } };

#endif /* FAN_CURVE_TABLE_H_ */
