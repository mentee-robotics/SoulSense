/*
 * configuration.h
 *
 *  Created on: Aug 16, 2023
 *      Author: nir
 */

#ifndef INC_CONFIGURATION_H_
#define INC_CONFIGURATION_H_

#define DEVICE_ID 20  //a random number (for now)
#define RX_BUFFER_SIZE 64 // need to adjust to the correct value
#define NUMBER_OF_SENSORS 8 // 8 contact sensors in the module
#define SIZE_OF_IMU_DATA 28 // 4 floats of quaternion , 3 floats of acceleration
#define SIZE_OF_SOLE_DATA 63 // 32 contact , 28 imu , 3 version

typedef enum {
	IDLE,
	READ_IMU,
	READ_ADC,
	RECEIVE_MESSAGE,
	TRANSMIT_MESSAGE
} States;




#endif /* INC_CONFIGURATION_H_ */
