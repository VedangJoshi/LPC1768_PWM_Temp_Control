/*
 *  Program to auto-control PWM of a DC fan to manage the
 *  CFM for proper cooling of electronic components using NXP LPC1768 MCU
 *
 *  Created on: Jun 12, 2020
 *      Author: Vedang Joshi
 */
#include "Fan_Curve_Table.h"

int main() {
	struct fan_curve_table_element *ptr = NULL;
	config_reg[0] = CONFIG;
	config_reg[1] = BIT_RES_12;
	config_reg[2] = MODE_4HZ;
	TMP102.write(addr, config_reg, 3);
	TMP102.write(addr, 0x00, 1);

	store_fan_curve_table();
	ptr = (struct fan_curve_table_element*) FLASH_SECTOR_29;
	pc.printf("\n\r==== Fan curve table ====");
	pc.printf("\n\r=========================");
	pc.printf("\n\r|  Temp (C)  |   PWM     |");
	pc.printf("\n\r=========================");
	for (int i = 0; i < 6; i++) {
		pc.printf("\n\r|   %3.1f     |    %3.1f    |", ptr->temp,
				ptr->pwm_factor);
		ptr++;
	}
	pc.printf("\n\r=========================");

	read_temp.attach(&temperature, 3); // Attach read_temp_func to the ticker
	pwm_ctl.period_us(pwm_period_us);
	while (1) {
		wait(2);

	}
}

