/*
 * Fan_Curve_Table.cpp
 *
 *  Created on: Jun 12, 2020
 *      Author: Vedang Joshi
 */

#include "Fan_Curve_Table.h"

void temperature() {
	float current_pwm = 0.0;
	TMP102.read(addr, temp_read, 2);
	float t = sensistivity * ((((temp_read[0] << 8) + temp_read[1])) >> 4);

	for (int i = 0; i < TABLE_SIZE - 1; i++) {
		if (t > fan_curve_table[i].temp && t <= fan_curve_table[i + 1].temp) {
			current_pwm = fan_curve_table[i + 1].pwm_factor;
		}
	}

	pwm_ctl = current_pwm;
	lcd.cls();
	lcd.printf("Temp = %.2f C\n", t);
	lcd.printf("PWM  = %3.1f pct", current_pwm * 100);
}

void store_fan_curve_table() {
	char *p = NULL;
	int r;
	static char mem[MEM_SIZE];

	p = (char*) &fan_curve_table;
	memset(&mem[0], 0, sizeof(mem));

	for (uint i = 0; i < sizeof(fan_curve_table); i++) {
		mem[i] = *(p + i);
	}

	r = iap.blank_check(TARGET_SECTOR, TARGET_SECTOR);

	if (r == SECTOR_NOT_BLANK) {
		pc.printf("\n\rSECTOR is not blank!");
		iap.prepare(TARGET_SECTOR, TARGET_SECTOR);
		r = iap.erase(TARGET_SECTOR, TARGET_SECTOR);
		pc.printf("\n\r Erase result = 0x%08X\n\r", r);
	}
	pc.printf("\n\r Sector %02d: %02d", 29, r);

	// prepare
	iap.prepare(TARGET_SECTOR, TARGET_SECTOR);

	// write
	r = iap.write(mem, sector_start_adress[TARGET_SECTOR], MEM_SIZE);

	pc.printf(
			"\n\r Copied: SRAM(0x%08X)->Flash(0x%08X) for %d bytes. (result=0x%08X)\r\n",
			mem, sector_start_adress[TARGET_SECTOR], MEM_SIZE, r);

	// compare
	r = iap.compare(mem, sector_start_adress[TARGET_SECTOR],
	MEM_SIZE);

	pc.printf("\n\r Compare result = \"%s\"\r\n",
			r ? "FAILED - Sector was probably not Blank before writing" : "OK");
}


