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

#define BITS_PER_CHANNEL 32     // OTHER_OPTION IN OTHER MEMS   8 16 24

enum _setStateI2S
{
    I2S_ENABLE = 0,
    I2S_DISABLE
};

typedef enum _setStateI2S setState_I2S_t;

typedef int32_t (*i2sInit_t)(uin8_t);
typedef int32_t (*i2sPin_t)(void);
typedef uint16_t (*i2sRead_t)(int32_t *, uint16_t);
typedef void(*i2sEnable_t)(setSate_I2S_t);

struct _inmp441 {
    i2sInit_t   i2s_init_fnc;
    i2sPin_t    i2s_set_pin_fnc;
    i2sRead_t   i2s_read_fnc;
    i2sEnable_t i2s_enable_fnc;
};

typedef struct _inmp441 inmp441_t;

void inmp441_initDriver(inmp441_t config);
uint16_t inmp441_record(int32_t *buffer, uint16_t len);
void inmp441_start_stop(setState_I2S_t enable);
int32_t inmp441_testing_vumeter(int32_t * buffer, uint16_t len);


#endif      /* PCSE_DRIVER_INMP441_INC_INMP441_H_ */