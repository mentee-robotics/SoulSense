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
void soul_init(SoulSense* soul_sense){
    memset(soul_sense->payload, 0, SIZE_OF_SOLE_DATA);
}

void soul_update_payload(SoulSense* soul_sense, ContactSensors* adc_data, IMU* imu_data, FwVersion* sole_version) {
    int index = 0;

    // Copy ContactSensors payload
    for (int i = 0; i < NUMBER_OF_SENSORS * 4; i++) {
        soul_sense->payload[index] = adc_data->payload[i];
        index++;
    }

    // Copy IMU payload
    for (int i = 0; i < SIZE_OF_IMU_DATA; i++) {
        soul_sense->payload[index] = imu_data->payload[i];
        index++;
    }

    // Copy FwVersion payload (version)
    for (int i = 0; i < VERSION_LEN; i++) {
        soul_sense->payload[index] = sole_version->version[i];
        index++;
    }
}

