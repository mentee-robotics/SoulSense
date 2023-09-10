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
//	comm->device_id = 0x13;
	set_device_address(comm);
	comm->send_message = false;
	comm->received_message = false;

	comm->TxHeader.Identifier = comm->device_id;
	comm->TxHeader.IdType=FDCAN_STANDARD_ID;
	comm->TxHeader.TxFrameType=FDCAN_DATA_FRAME;
	comm->TxHeader.DataLength=FDCAN_DLC_BYTES_64;  //8 uint32_t values = 32 bytes
	comm->TxHeader.ErrorStateIndicator=FDCAN_ESI_ACTIVE;
	comm->TxHeader.BitRateSwitch=FDCAN_BRS_OFF;
	comm->TxHeader.FDFormat=FDCAN_FD_CAN;
	comm->TxHeader.TxEventFifoControl=FDCAN_NO_TX_EVENTS;
	comm->TxHeader.MessageMarker=0;

	// Set number of extended ID filters to 1

	comm->filter.IdType = FDCAN_STANDARD_ID;
	comm->filter.FilterIndex = 0;
	comm->filter.FilterType = FDCAN_FILTER_MASK;
	comm->filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
	comm->filter.FilterID1 = comm->device_id;
	comm->filter.FilterID2 = 0x7FF;
	HAL_FDCAN_ConfigFilter(&comm->fdcan, &comm->filter);
	HAL_FDCAN_ConfigGlobalFilter(&comm->fdcan, FDCAN_REJECT, FDCAN_REJECT, FDCAN_REJECT_REMOTE, FDCAN_REJECT_REMOTE);

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

	int flag = 0;
	if (comm->RxHeader.Identifier == comm->device_id) {  //simple logic for now, its a flag to send a message back from the device
		flag = 1;
	}
	return flag;
}


void set_device_address(CommController *comm)
{
    uint8_t bit0 = (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10) == GPIO_PIN_RESET); // Reads PA15
    uint8_t bit1 = (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11) == GPIO_PIN_RESET); // Reads PC10
    uint8_t bit2 = (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12) == GPIO_PIN_RESET); // Reads PC11

    comm->device_id = (bit2 << 2) | (bit1 << 1) | bit0;
}


