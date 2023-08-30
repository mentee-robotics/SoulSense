/*
 * commcontroller.c
 *
 *  Created on: Aug 16, 2023
 *      Author: nir
 */


#include "fdcan.h"
#include "configuration.h"
#include "commcontroller.h"
#include <string.h>



void comm_controller_init(FDCAN_HandleTypeDef* fdcan, CommController *comm){

	comm->fdcan = *fdcan;
	comm->device_id = DEVICE_ID;
	comm->send_message = false;
	comm->received_message = false;

	comm->TxHeader.Identifier = comm->device_id;
	comm->TxHeader.IdType=FDCAN_STANDARD_ID;
	comm->TxHeader.TxFrameType=FDCAN_DATA_FRAME;
	comm->TxHeader.DataLength=FDCAN_DLC_BYTES_32;  //8 uint32_t values = 32 bytes
	comm->TxHeader.ErrorStateIndicator=FDCAN_ESI_ACTIVE;
	comm->TxHeader.BitRateSwitch=FDCAN_BRS_OFF;
	comm->TxHeader.FDFormat=FDCAN_FD_CAN;
	comm->TxHeader.TxEventFifoControl=FDCAN_NO_TX_EVENTS;
	comm->TxHeader.MessageMarker=0;

	memset(comm->RxData , 0 , RX_BUFFER_SIZE);

	HAL_FDCAN_Start(&comm->fdcan);
	HAL_FDCAN_ActivateNotification(&comm->fdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE,0);

}


void send_message(CommController *comm , uint8_t *payload) {
	if(HAL_FDCAN_AddMessageToTxFifoQ(&comm->fdcan, &comm->TxHeader, payload) != HAL_OK)//
		{
		  Error_Handler();
		}
}

int process_received_message(CommController *comm) {
	uint8_t data = comm->RxData[0];
	int flag = 0;
	if (comm->RxHeader.Identifier == DEVICE_ID) {  //simple logic for now, its a flag to send a message back from the device
		flag = 1;
	}
	return flag;
}
