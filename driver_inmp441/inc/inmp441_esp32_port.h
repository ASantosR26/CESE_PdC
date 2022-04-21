/**
 * @file inmp441_esp32_port.h
 * @author Alexander Santos (asantosr@uni.pe)
 * @brief 
 * @version 0.1
 * @date 2022-04-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef     PCSE_DRIVER_INMP441_INC_INMP441_ESP32_PORT_H_
#define     PCSE_DRIVER_INMP441_INC_INMP441_ESP32_PORT_H_

#include "inmp441.h"
#include "driver/i2s.h"

int32_t i2s_init_esp32_port(void);
int32_t i2s_set_pin_esp32_port(void);
uint16_t i2s_read_esp32_port(int32_t *buffer, uint16_t len);

#endif      /* PCSE_DRIVER_INMP441_INC_INMP441_ESP32_PORT_H_ */