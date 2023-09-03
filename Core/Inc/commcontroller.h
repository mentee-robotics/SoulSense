/*
 * commcontroller.h
 *
 *  Created on: Aug 16, 2023
 *      Author: nir
 */

#ifndef INC_COMMCONTROLLER_H_
#define INC_COMMCONTROLLER_H_

#include "fdcan.h"
#include "configuration.h"
#include <stdbool.h>


typedef struct {
	bool send_message;        // The desired force or torque setpoint       // The actual measured force or torque
	bool received_message;
    FDCAN_TxHeaderTypeDef TxHeader;
	FDCAN_RxHeaderTypeDef RxHeader;
	FDCAN_HandleTypeDef fdcan;
	FDCAN_FilterTypeDef filter;
	uint8_t RxData[RX_BUFFER_SIZE];
	uint16_t device_id;
} CommController;





void comm_controller_init(FDCAN_HandleTypeDef *fdcan, CommController *comm);

void send_message(CommController *comm , uint8_t *payload);

//void set_device_address(CommController *comm);

int process_received_message(CommController *comm);

#endif /* INC_COMMCONTROLLER_H_ */
