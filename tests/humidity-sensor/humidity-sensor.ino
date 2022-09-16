#include "DHT.h"
#define pinDatos D4  //GPIO4 = D2 en D1 Mini, D4 en ESP32
DHT sensorTH (pinDatos, DHT11);    //Crea objeto sensorTH
void setup() {
 Serial.begin (115200);
 Serial.println ("***** Lectura DHT22 *****");
 sensorTH.begin ();   //Inicializa pines del sensor
 
}
void loop() {
  delay (2000);
  
  //Lee valores de temperatura y humedad
  float humedad = sensorTH.readHumidity();
  float temperatura = sensorTH.readTemperature();
  
  //Mostrar valores leídos
  Serial.print ("Temperatura = ");
  Serial.print (temperatura);
  Serial.println (" ºC");
  Serial.print ("Humedad = ");
  Serial.print (humedad);
  Serial.println (" %");
  
}
