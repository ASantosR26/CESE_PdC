#include <stdio.h>
#include <string.h>
#include "inmp441_esp32_port.h"
#include "inmp441.h"

void app_main(void)
{
    uint16_t len = 128;
    int32_t raw_sample[128];
    int32_t mean_sample = 0;

    printf("Init I2S Test with INMP441\r\n");

    inmp441_t str_mems_driver;

    printf("Cargando estructura del driver INMP441 - I2S\r\n");
    str_mems_driver.i2s_init_fnc    = i2s_init_esp32_port;
    str_mems_driver.i2s_set_pin_fnc = i2s_set_pin_esp32_port;
    str_mems_driver.i2s_read_fnc    = i2s_read_esp32_port;
    str_mems_driver.i2s_enable_fnc  = i2s_ctlEnable_esp32_port;

    printf("Inicializando el driver INMP441 - I2S\r\n");
    inmp441_initDriver(str_mems_driver);

    while ( 1 )
    {
        uint16_t number_sample = inmp441_record(raw_sample, len); 
        
        /********* Test Vumeter ******/
        int32_t ind_vumeter = inmp441_testing_vumeter(raw_sample, number_sample);
        printf("Vumeter data: %d \n", ind_vumeter);
        /********* End Vumeter ********/
        
        /**** Delay de 1 segundo para observar los datos por consola *****/
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
