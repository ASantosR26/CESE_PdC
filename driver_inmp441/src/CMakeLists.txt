idf_component_register(SRCS "inmp441.c" "inmp441_esp32_port.c" "main.c"
                    INCLUDE_DIRS "../inc"
                    REQUIRES mbedtls
                    PRIV_REQUIRES console spiffs)
