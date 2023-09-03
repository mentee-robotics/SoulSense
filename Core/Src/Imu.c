/*
 * Imu.c
 *
 *  Created on: Aug 16, 2023
 *      Author: nir
 */

#include "Imu.h"
#include "configuration.h"
#include "i2c.h"

#include <string.h>
#include <stdio.h>
#include "bno055.h"

#include "stm32g4xx_hal.h"
#include "gpio.h"
#include "i2c.h"
#include <stdlib.h>



#define SENSOR_BUS I2C1

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


// Initializing the IMU
void imu_init(I2C_HandleTypeDef* i2c,IMU* imu) {
    // Ensure that the BNO pointer is allocated (if using dynamic memory)
    imu->bno = (bno055_t*) malloc(sizeof(bno055_t));

    if (imu->bno == NULL) {
        // Handle memory allocation error
        return;
    }

    imu->bno->i2c = i2c;
    imu->bno->addr = BNO_ADDR_ALT;
    imu->bno->mode = BNO_MODE_IMU;

    imu->errInit = bno055_init(imu->bno);

    bno055_set_unit(imu->bno, BNO_TEMP_UNIT_C, BNO_GYR_UNIT_DPS,
    	                      BNO_ACC_UNITSEL_M_S2, BNO_EUL_UNIT_DEG); //set correct units!
}

// Reading data
void imu_read_data(IMU* imu) {
	//TODO more checking
	if (imu->errInit == BNO_OK ) {  //checks that the imu has been properly initialized.
		imu->errGyr = imu->bno->gyro(imu->bno, &imu->gyroscope);
		imu->errAcc = imu->bno->acc(imu->bno, &imu->accelerometer);
	    imu->errQua = imu->bno->quaternion(imu->bno, &imu->quaternion);
	}
}

// Cleanup
void IMU_Deinit(IMU* imu) {
    if (imu->bno) {
        free(imu->bno);
    }
}

void imu_update_payload(IMU* imu) {
    // Starting index for the payload
    int index = 0;

    // Convert quaternion values to byte array format.
    float quaternion_values[4] = {
        imu->quaternion.x,
        imu->quaternion.y,
        imu->quaternion.z,
        imu->quaternion.w
    };

    for (int i = 0; i < 4; i++) {
        memcpy(&imu->payload[index], &quaternion_values[i], 4);
        index += 4;
    }

    // Convert accelerometer values to byte array format.
    float accel_values[3] = {
        imu->accelerometer.x,
        imu->accelerometer.y,
        imu->accelerometer.z,
    };

    for (int i = 0; i < 3; i++) {
        memcpy(&imu->payload[index], &accel_values[i], 4);
        index += 4;
    }
}

