/*
 * Imu.h
 *
 *  Created on: Aug 16, 2023
 *      Author: nir
 */

#ifndef INC_IMU_H_
#define INC_IMU_H_

#include "configuration.h"
#include "i2c.h"
#include "bno055.h"

typedef struct {  //assuming 6 dof IMU
    bno055_t* bno;
    bno055_vec3_t gyroscope;
    bno055_vec3_t accelerometer;
    bno055_vec4_t quaternion;
    error_bno errInit;
    error_bno errGyr;
    error_bno errAcc;
    error_bno errQua;
    uint8_t payload[SIZE_OF_IMU_DATA];

} IMU;

void imu_init(I2C_HandleTypeDef* i2c, IMU* imu);

void imu_read_data(IMU* imu);

void imu_update_payload(IMU* imu);

#endif /* INC_IMU_H_ */
