### pipe-arduino

# P.I.P.E

[![Logo de Pipe](https://raw.githubusercontent.com/Proyecto-Pipe/pipe-frontend/main/public/logo.png "Logo de Pipe")](# "Logo de Pipe")

### Proyecto Invernadero Pedagógico Estudiantil

Presentación el proyecto: https://youtu.be/kD3DB3PJZvg

**P.I.P.E** es un invernadero inteligente enfocado a instituciones educativas que busca promover en sus estudiantes un compromiso hacia el medio ambiente.

- **Didáctico**: Orientado al aprendizaje para todos los rangos de edad.

- **Asequible**: Creado con componentes de electrónica y programación.

- **Sostenible**: Encaminado al cumplimiento el [Objetivo de Desarrollo Sostenible # 13][objetivo de desarrollo sostenible # 13].

## Documentación

El código de P.I.P.E está dividido en 3 partes. **En cada uno de los repositorios se encuentra documentación más detallada**.

[![documentacion imagen](https://github.com/Proyecto-Pipe/.github/blob/main/pipe-architecture.jpg?raw=true "documentacion imagen")](# "documentacion imagen")

- **pipe-arduino:** Sketch de Arduino programado en C++. Su función es recolectar mediante sensores y posteriormente enviar al servidor la humedad, temperatura y luminosidad del invernadero y verifica cada determinado tiempo si en el servidor hay una petición pendiente para activar una bombilla o una bomba de agua. Este corre en cualquier placa de desarrollo, se recomienda ESP 32.

- **[pipe-server:][pipe-server]** Servidor escrito con Node.js. Este recibe los datos (humedad, temperatura, luminosidad) de la placa y los envía al frontend del usuario mediante una API. Mediante la misma API recibe las peticiones (activar bombilla, activar bomba de agua) del usuario para que la placa procese y ejecute. Corre en cualquier servicio de hosting que soporte Javascript.

- **[pipe-frontend:][pipe-frontend]** Página web programada con React. Muestra los datos del invernadero y envía las peticiones al servidor. Es hosteado mediante Github Pages.

## Documentación pipe-arduino

### Dependencias

El proyecto se edita y sube a la placa mediante el editor de código [Arduino IDE][arduino ide]. Este debe estar configurado para soportar la placa ESP 8266.

Placa: ESP 8266 new NodeMcu V3.
Soporte de placa: NodeMCU 1.0 (ESP-12E Module).

Librerías:

- [DHT sensor library][dht sensor library] (por Adafruit) 1.4.3
- [ArduinoJson][arduinojson] (por Benoit Blanchon) 6.19.4
- ESP8266WiFi (incluida en el soporte para ESP 8266)
- ESP8266HTTPClient (incluida en el soporte para ESP 8266)

### Estructura de archivos:

- **/pipe-arduino.ino**: Archivo principal.

- **/settings.h**: Archivo con las siguientes variables de entorno:

  - **VERSION**: String (Ej: "1.0.3").
  - **FLASH_PIN**: Pin (Ej: D7, D2) con led para debugging.
  - **DHT_PIN**: Pin con sensor DHT.
  - **DHT_TYPE**: Tipo de sensor DHT (Ej: DHT11, DHT22).
  - **PUMP_RELAY_PIN**: Pin con bomba de agua.
  - **PUMP_DURATION**: Duración en milisegundos del riego (Ej: 2000).
  - **BULB_PIN**: Pin con bombilla.
  - **PHOTORESISTOR_PIN**: Pin con fotoresistencia.
  - **SOUL_MOISTURE_SENSOR_PIN**: Pin analógico con sensor de humedad del suelo (Ej: A0)
  - **BUFFER_SIZE**: Tamaño del buffer de peticiones http (Ej: 174).
  - **SERIAL_BAUD_RATE**: Baud rate para debuggear en monitor serial (Ej: 115200).
  - **URL**: Url del servidor pipe-server. (Ej: "https://pipe-server.herokuapp.com/")
  - **PORT**: Puerto a acceder en el servidor pipe-server.
  - **API_PASSWORD**: Contraseña del servidor pipe-server.
  - **WIFI_SSID**: SSID de la red wifi a la que se conectará la placa.
  - **WIFI_PASSWORD**: Contraseña de la red wifi a la que se conectará la placa.

- **/flash.h**: Declaración de la función ` void flash(int time, int times);` que hace parpadear el led especificado en `FLASH_PIN`, el tiempo indicado la cantidad de veces indicada. (Definición de la función en **/flash.ino**).
- **/initWifi.h**: Declaración de la función `void initWifi();` que conecta la placa a internet. (Definición de la función en **/initWifi.cpp**).
- **/PIPE.h**: Declaración de la clase `PIPE` encargada de guardar y modificar el estado de las variables del invernadero. (Definición de la clase en **/PIPE.cpp**).
- **/PIPEInstance.h**: Declaración de la instancia `PIPEInstance` de la clase `PIPE` siguiendo el patrón [Singleton][singleton]. (Definición en **/PIPEInstance.cpp**).
- **/request.h**: Declaración de funciones `void getPipe();` y `void postPipe();` encargadas de manejar las peticiones HTTP. (Definición de las funciones en **/request.cpp**).

## Autores

P.I.P.E ha sido creado por **[Julian Franco][julian franco]**, **Zaida Guzman** y **[David Hurtado][david hurtado]**, estudiantes del **[Colegio Agustiniano Norte][colegio agustiniano norte]**, apoyados por el profesor **[William Andres Granada Campos][william andres granada campos]**.

[objetivo de desarrollo sostenible # 13]: https://www.un.org/sustainabledevelopment/es/climate-change-2/ "Objetivo de Desarrollo Sostenible # 13"
[david hurtado]: https://santigo171.github.io/ "David Hurtado"
[william andres granada campos]: https://www.linkedin.com/in/william-andres-granada-campos-b4017116/ "William Andres Granada Campos"
[colegio agustiniano norte]: https://agustinianonorte.edu.co/ "Colegio Agustiniano Norte"
[pipe-arduino]: https://github.com/proyecto-pipe/pipe-arduino "pipe-arduino"
[julian franco]: https://www.instagram.com/Julianfranco_07/ "Julian Franco"
[pipe-server]: https://github.com/proyecto-pipe/pipe-server "pipe-server"
[pipe-frontend]: https://github.com/proyecto-pipe/pipe-frontend "pipe-frontend"
[arduino ide]: https://www.arduino.cc/en/software "Arduino IDE"
[arduinojson]: https://arduinojson.org/?utm_source=meta&utm_medium=library.properties "ArduinoJson"
[dht sensor library]: https://github.com/adafruit/DHT-sensor-library "DHT sensor library"
[singleton]: https://refactoring.guru/design-patterns/singleton "Singleton"
