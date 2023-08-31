/*
 * version.c
 *
 *  Created on: Aug 30, 2023
 *      Author: nir
 */


#include "version.h"

void version_init(FwVersion* version){
	version->version[0] = HW_VERSION;
	version->version[1] = SW_MAJOR_VERSION;
	version->version[2] = SW_MINOR_VERSION;
}

