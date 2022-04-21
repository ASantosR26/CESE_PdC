/**
 * @file inmp441.h
 * @author Alexander Santos (asantosr@uni.pe)
 * @brief 
 * @version 0.1
 * @date 2022-04-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef     PCSE_DRIVER_INMP441_INC_INMP441_H_
#define     PCSE_DRIVER_INMP441_INC_INMP441_H_

#include <stdio.h>
#include <stdint.h>

typedef int32_t (*i2sInit_t)(void);
typedef int32_t (*i2sPin_t)(void);
typedef uint16_t (*i2sRead_t)(int32_t, uint16_t);

struct _inmp441 {
    i2sInit_t   i2s_init_fnc;
    i2sPin_t    i2s_set_pin_fnc;
    i2sRead_t   i2s_read_fnc;
};

typedef struct _inmp441 inmp441_t;

void inmp441_initDriver(inmp441_t config);
void inmp441_record(int32_t *buffer, uint16_t len);



#endif      /* PCSE_DRIVER_INMP441_INC_INMP441_H_ */