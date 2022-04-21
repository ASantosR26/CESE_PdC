# _DRIVER INMP441_

Driver I2S para la lectura de datos I2S del micrófono INMP41, con el ESP32.


## Uso del programa

Para probar el programa necesitará el micrófono lINMP441 y el ESP32. El firmware fue probado en Visual studio Code.

Para clonar el repositorio: `git clone git@github.com:ASantosR26/CESE_PdC.git`


## Estructura de la carpeta

Los proyectos ESP-IDF se construyen usando CMake. La configuración de compilación del proyecto está contenida en `CMakeLists.txt` archivos que proporcionan un conjunto de directivas e instrucciones que describen los archivos fuente y los destinos del proyecto
 
A continuación se muestra una breve explicación de los archivos restantes en la carpeta del proyecto.

```
├── build
├── CMakeLists.txt
├── inc
│   └── inmp441_esp32_port.h
│   └── inmp441.h
├── src
│   ├── CMakeLists.txt
│   └── inmp441_esp32_port.c
│   └── inmp441.c
│   └── main.c
├── README.md 
└── sdkconfig              
```

