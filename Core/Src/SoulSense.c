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
void soul_init(SoulSense* soul_sense, ContactSensors* adc_data, IMU* imu_data, FwVersion* sole_version){
    memset(soul_sense->payload, 0, SIZE_OF_SOLE_DATA);
    soul_sense->adc_data = *adc_data; // Dereference the pointers to copy the data
    soul_sense->imu_data = *imu_data;
    soul_sense->sole_version = *sole_version;
}

void soul_update_payload(SoulSense* soul_sense) {
    int index = 0;

    // Copy ContactSensors payload
    memcpy(&soul_sense->payload[index], soul_sense->adc_data.payload, NUMBER_OF_SENSORS*4);
    index += sizeof(soul_sense->adc_data.payload);

    // Copy IMU payload
    memcpy(&soul_sense->payload[index], soul_sense->imu_data.payload, SIZE_OF_IMU_DATA);
    index += sizeof(soul_sense->imu_data.payload);

    // Copy FwVersion payload (version)
    memcpy(&soul_sense->payload[index], soul_sense->sole_version.version, VERSION_LEN);
}

