/*
 * modbus_CRC.h
 *
 *  Created on: Sep 26, 2025
 *      Author: Anamitra Sarkar
 */

#ifndef MY_FILES_HEADERS_MODBUS_CRC_H_
#define MY_FILES_HEADERS_MODBUS_CRC_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Control_Variables.h"
#include "Device/driverlib/sci.h"
#include "device.h"
#include "driverlib.h"

extern uint16_t crc16(uint16_t *buffer, uint16_t buffer_length);



#endif /* MY_FILES_HEADERS_MODBUS_CRC_H_ */
