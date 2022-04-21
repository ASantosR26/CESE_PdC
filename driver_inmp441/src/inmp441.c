/**
 * @file inmp441.c
 * @author Alexander Santos (asantosr@uni.pe)
 * @brief 
 * @version 0.1
 * @date 2022-04-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "inmp441.h"

static inmp441_t inmp441_control;

void inmp441_initDriver(inmp441_t config)
{
    inmp441_control.i2s_init_fnc    = config.i2s_init_fnc;
    inmp441_control.i2s_set_pin_fnc = config.i2s_set_pin_fnc;
    inmp441_control.i2s_read_fnc    = config.i2s_read_fnc;
    
    inmp441_control.i2s_init_fnc();
    inmp441_control.i2s_set_pin_fnc();
}

void inmp441_record(int32_t *buffer, uint16_t len)
{
    inmp441_control.i2s_read_fnc(buffer, len);
}


