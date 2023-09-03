/*
 * SoulSense.c
 *
 *  Created on: Aug 30, 2023
 *      Author: nir
 */


#include "SoulSense.h"
#include "version.h"
#include "Imu.h"
#include "contact_sensors.h"
#include "configuration.h"

// Adjust soul_init to use pointers for the parameters
void soul_init(SoulSense* soul_sense , I2C_HandleTypeDef* i2c , ADC_HandleTypeDef *adc){
	ADC_init(adc , soul_sense->contact_sensors);
	imu_init(i2c , soul_sense->imu);
	version_init(soul_sense->version);
    memset(soul_sense->payload, 0, SIZE_OF_SOLE_DATA);
}

void soul_update_payload(SoulSense* soul_sense) {
	imu_update_payload(soul_sense->imu);
	ADC_update_payload(soul_sense->contact_sensors);
    int index = 0;

    // Copy ContactSensors payload
    for (int i = 0; i < NUMBER_OF_SENSORS * 4; i++) {
        soul_sense->payload[index] = soul_sense->contact_sensors->payload[i];
        index++;
    }

    // Copy IMU payload
    for (int i = 0; i < SIZE_OF_IMU_DATA; i++) {
        soul_sense->payload[index] = soul_sense->imu->payload[i];
        index++;
    }

    // Copy FwVersion payload (version)
    for (int i = 0; i < VERSION_LEN; i++) {
        soul_sense->payload[index] = soul_sense->version->version[i];
        index++;
    }
}

