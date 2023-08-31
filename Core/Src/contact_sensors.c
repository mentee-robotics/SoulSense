/*
 * contact_sensors.c
 *
 *  Created on: Aug 16, 2023
 *      Author: nir
 */
#include "contact_sensors.h"
#include "configuration.h"
#include "adc.h"
#include "dma.h"

void ADC_init(ADC_HandleTypeDef *adc, ContactSensors *sensors){
	sensors->adc = adc;
	memset(sensors->adcValues , 0 , sizeof(sensors->adcValues));
	HAL_ADC_Start_DMA(sensors->adc, sensors->adcValues, NUMBER_OF_SENSORS);
}


void ADC_update_payload(ContactSensors *sensors) {
    // Pointer to the current position in the payload
    uint8_t *payloadPtr = sensors->payload;

    // Iterate through each ADC value
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        // Extract each byte from the 32-bit ADC value and flip the MSB for the most significant byte
        *payloadPtr++ = ((sensors->adcValues[i] >> 24) & 0xFF) ^ 0x80;  // MSB with flipped bit
        *payloadPtr++ = (sensors->adcValues[i] >> 16) & 0xFF;
        *payloadPtr++ = (sensors->adcValues[i] >> 8) & 0xFF;
        *payloadPtr++ = sensors->adcValues[i] & 0xFF;                    // LSB
    }
}

