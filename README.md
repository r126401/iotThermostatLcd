**    CRONOTERMOSTATO WIFI **

Primera version estable del cronotermostato wifi.

Caracteristicas:

- Programacion libre de los dias de la semana. En cada intervalo se programa la temperatura.

- Temperatura umbral por defecto cuando no hay programacion.



**Instalacion**

Para poder continuar con el desarrollo es necesario hacer las siguientes tareas.



1. git clone --recursive git@github.com:r126401/iotThermostatLcd.git

2. Descargar los componentes adicionales del proyeceo.
   
   1. git clone --recursive git@github.com:r126401/components.git
   
   2. editar el fichero CMakeLists.txt del proyecto iotThermostatLcd
   
   3. set (EXTRA_COMPONENT_DIRS "../components"). Será el directorio en el que se hayan dejado los componentes.
   
   4. idf.py build
   
   5. idf.py erase_flash
   
   6. idf.py flash
   
   7. 


