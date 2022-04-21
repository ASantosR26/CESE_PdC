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
#include <stdbool.h>

static inmp441_t inmp441_control;

/**
 * @brief Inicializa el driver inmp441.
 * 
 * @param config Estructura de configuración para el driver.
 */
void inmp441_initDriver(inmp441_t config)
{
    inmp441_control.i2s_init_fnc    = config.i2s_init_fnc;
    inmp441_control.i2s_set_pin_fnc = config.i2s_set_pin_fnc;
    inmp441_control.i2s_read_fnc    = config.i2s_read_fnc;
    inmp441_control.i2s_enable_fnc   = config.i2s_enable_fnc;
    
    // Inicializa las configuraciones de pines e I2S
    inmp441_control.i2s_init_fnc(BITS_PER_CHANNEL);
    inmp441_control.i2s_set_pin_fnc();
}

/**
 * @brief Función que realiza la lectura de datos I2S.
 * 
 * @param buffer Dirección de memoria a partir donde se almacenará la lectura I2S.
 * @param len Cantidad de muestras que se almacenará.
 * @return uint16_t Devuelve la cantidad de muuestras que ha leído.
 */
uint16_t inmp441_record(int32_t *buffer, uint16_t len)
{
    len = inmp441_control.i2s_read_fnc(buffer, len);
    if ( len > 0 )
    {
        for ( uint16_t i = 0; i < len; i++ )
        {
            // La información está en 24(MSB) bits de los 32 que envía, revisar datasheet INMP441
            *(buffer + i) = *(buffer + i) >> 8;
        }
    }
    return len;
}

/**
 * @brief Función para detener o iniciar el puerto i2s
 * 
 * @param enable Variable para habilita o no el i2s.
 */
void inmp441_start_stop(setState_I2S_t enable)
{
    inmp441_control.i2s_enable_fnc(enable);
}

/**
 * @brief Vúmetro de los datos leídos por el micrófono
 * 
 * @param buffer Buffer donde estan almacenados la captura de sonido del microfono
 * @param len    Longitud del buffer
 * @return int32_t  La amplitud de los datos enviados.
 */
int32_t inmp441_testing_vumeter(int32_t * buffer, uint16_t len)
{
    int32_t mean_sample;
    int32_t min_sample = 10000;
    int32_t max_sample = -10000;

    for(uint16_t i = 0; i < len; i++)
    {
        mean_sample += buffer[i];
    }
    mean_sample /= len;
    for(uint16_t i = 0; i < len; i++)
    {
        min_sample = (buffer[i] < min_sample) ? buffer[i] : min_sample;
        max_sample = (buffer[i] > max_sample) ? buffer[i] : max_sample;
    }
    return max_sample - min_sample;
}

