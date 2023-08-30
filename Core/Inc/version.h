/*
 * version.h
 *
 *  Created on: Aug 10, 2023
 *      Author: yonatan
 */

#ifndef INC_VERSION_H_
#define INC_VERSION_H_
#include <stdint.h>

#define HW_VERSION       1 // Numeric value

#define SW_MAJOR_VERSION 0 // Numeric value
#define SW_MINOR_VERSION 1 // Numeric value


#define STRINGIZE_NX(A) #A
#define STRINGIZE(A) STRINGIZE_NX(A)
#define VERSION_STRING STRINGIZE(HW_VERSION) STRINGIZE(SW_MAJOR_VERSION) STRINGIZE(SW_MINOR_VERSION)
#define VERSION_LEN 3


typedef struct { //TODO
	uint8_t version[VERSION_LEN];
} FwVersion;

void version_init(FwVersion* version);

#endif /* INC_VERSION_H_ */
