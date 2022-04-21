/**
 * @file inmp441_esp32_port.c
 * @author Alexander Santos (asantosr@uni.pe)
 * @brief 
 * @version 0.1
 * @date 2022-04-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "inmp441_esp32_port.h"

#define I2S_BCK_IO              (GPIO_NUM_32)
#define I2S_WS_IO               (GPIO_NUM_25)
#define I2S_DI_IO               (GPIO_NUM_33)

#define SAMPLE_RATE_I2S_PORT    (40000)

#define BLOCK_SIZE              (64)
#define NUMBER_BLOCK            (8)

static i2s_config_t i2s_config;
static i2s_pin_config_t pin_config;

/**
 * @brief Configura los parámetros del protocolo I2S
 * 
 * @param bits_per_channel  Indica los bits que se van a transmitir en cada canal 
 * @return int32_t Retorna la devolución de i2s_driver_install
 */
int32_t i2s_init_esp32_port(uint8_t bits_per_channel)
{
    // Configuraciones del puerto I2S
    // De acuerdo a "sample_rate" se obtiene la frecuencia del reloj I2S
    // SCK = (sample_rate) * (bits_per_chhanel) * (#canales)
    i2s_config.mode                 = I2S_MODE_MASTER | I2S_MODE_RX;            // Maestro: Genera la señal del reloj, Rx: Recibe los datos(SD)
    i2s_config.sample_rate          = SAMPLE_RATE_I2S_PORT;                 
    i2s_config.bits_per_sample      = (i2s_bits_per_chan_t)bits_per_channel;    // Depende del Micrófono.
    i2s_config.channel_format       = I2S_CHANNEL_FMT_ONLY_LEFT;                // Depende de la aplicación (escogido por el usuario).
    i2s_config.communication_format = I2S_COMM_FORMAT_STAND_I2S;                
    i2s_config.dma_desc_num         = NUMBER_BLOCK;                             // Escogido por el usuario.
    i2s_config.dma_frame_num        = BLOCK_SIZE;                               // Escogido por el usuario.                   
    i2s_config.use_apll             = true;
    i2s_config.intr_alloc_flags     = ESP_INTR_FLAG_LEVEL1;

    int32_t flag = i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);      // Instala e inicia el driver I2S propio de ESP32.

    
    return flag;
}

/**
 * @brief Setea los pines a utilizar en el ep32
 * 
 * @return int32_t retorna la devolución de i2S_set_pin
 */
int32_t i2s_set_pin_esp32_port(void)
{
    // Configuracón del número de pines.
    pin_config.mck_io_num           = I2S_PIN_NO_CHANGE;
    pin_config.bck_io_num           = I2S_BCK_IO;
    pin_config.ws_io_num            = I2S_WS_IO;
    pin_config.data_out_num         = I2S_PIN_NO_CHANGE;
    pin_config.data_in_num          = I2S_DI_IO;

    int32_t flag = i2s_set_pin(I2S_NUM_0, &pin_config);    
  
    return flag;
}

/**
 * @brief Realiza la lectura de los datos del puerto I2S
 * 
 * @param buffer buffer de destino donde se almacenan los datos
 * @param len    Longitud del buffer
 * @return uint16_t Devuelve la cantidad de muestras leídas
 */
uint16_t i2s_read_esp32_port(int32_t *buffer, uint16_t len)
{
    uint16_t n_samples = 0;

    int32_t flag = i2s_read(I2S_NUM_0, (void *)buffer, 
                            len * sizeof(int32_t),&n_samples, 0);

    n_samples = (flag == ESP_OK) ? (n_samples / sizeof(int32_t)) : 0;
    
    return n_samples;
}

/**
 * @brief Control del start - stop del puestro I2S
 * 
 * @param enable variable del tipo setState_I2S_t
 */
void i2s_ctlEnable_esp32_port(setState_I2S_t enable)
{
    if (enable == I2S_ENABLE)
    {
        i2s_start(I2S_NUM_0);
    }
    else if(enable == I2S_DISABLE)
    {
        i2s_stop(I2S_NUM_0);
    }
}