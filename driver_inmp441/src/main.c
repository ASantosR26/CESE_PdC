#include <stdio.h>
#include "inmp441_esp32_port.h"
#include "inmp441.h"

void app_main(void)
{
    uint16_t len = 250;
    int32_t sample_raw[len];

    printf("Init I2S Test with INMP441\r\n");

    inmp441_t str_mems_driver;

    printf("Cargando estructura del driver INMP441 - I2S\r\n");
    str_mems_driver.i2s_init_fnc    = i2s_init_esp32_port;
    str_mems_driver.i2s_set_pin_fnc = i2s_set_pin_esp32_port;
    str_mems_driver.i2s_read_fnc    = i2s_read_esp32_port;

    printf("Inicializando el driver INMP441 - I2S\r\n");
    inmp441_initDriver(str_mems_driver);

    /*while ( 1 )
    {
        inmp441_record(sample_raw, len); 
    }*/
}
