/*
 * contact_sensors.h
 *
 *  Created on: Aug 16, 2023
 *      Author: nir
 */

#ifndef INC_CONTACT_SENSORS_H_
#define INC_CONTACT_SENSORS_H_

#include "configuration.h"
#include "adc.h"
#include "dma.h"

typedef struct {
	uint32_t adcValues[NUMBER_OF_SENSORS];
	ADC_HandleTypeDef* adc;
	uint8_t payload[NUMBER_OF_SENSORS * 4];
}ContactSensors;

void ADC_init(ADC_HandleTypeDef *adc , ContactSensors *sensors);

void ADC_update_payload(ContactSensors *sensors);


#endif /* INC_CONTACT_SENSORS_H_ */
