/*
 * SoulSense.h
 *
 *  Created on: Aug 30, 2023
 *      Author: nir
 */

#ifndef INC_SOULSENSE_H_
#define INC_SOULSENSE_H_
#include "version.h"
#include "Imu.h"
#include "contact_sensors.h"
#include "configuration.h"
#include <stdint.h>
#include <string.h>

typedef struct {
	ContactSensors adc_data;
	IMU imu_data;
    FwVersion sole_version;
    uint8_t payload[SIZE_OF_SOLE_DATA];
} SoulSense;


void soul_init(SoulSense* soul_sense, ContactSensors* adc_data , IMU* imu_data , FwVersion* sole_version);

void soul_update_payload(SoulSense* soul_sense);



#endif /* INC_SOULSENSE_H_ */
