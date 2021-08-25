/*

Autor: Lalo del canal de MecatronicaMADE.
Curso: Node-RED Basico II

 Ejemplo de configuracion basica MQTT Publicador.

Basado en la libreria "PubSubClient.h" de Nick O' Leary
Conecta con la red WiFi, luego
conecta con un Broker MQTT despues:

- Publica un valor simulado de temperatura.

 */
//---- Incluimos librerias ----//
#include<ESP8266WiFi.h>
#include<PubSubClient.h>
//#include"credenciales.h"

//---- Parametros de red WIFI (descomentar)----//
//const char* ssid = "nombre_red";
//const char* contrasena = "password";

//---- Parametros MQTT ----//
const char* servidor_mqtt = "IP/URL_Broker";
int puerto_mqtt = 1883; // 8883

//---- Instancias wifi y cliente MQTT ----//
WiFiClient ClientEsp;
PubSubClient client(ClientEsp);

//---- Conexion a wifi ----//
void configuracion_wifi(){
  delay(10);
  WiFi.begin(ssid, contrasena);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
  }
}
//---- Conexion a Broker MQTT ----//
void reconnect(){
  while (!client.connected()){
    Serial.println("Intentando conexion MQTT...");
    if(client.connect("ESP8266Client")){
      Serial.println("Conecatdo");
    } else {
      Serial.print("Falla, estado = ");
      Serial.println(client.state());
      Serial.println("Intentando conexion nuevamente en 5 segundos...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  configuracion_wifi();
//---- Establecemos parametros de Broker ----//
  client.setServer(servidor_mqtt, puerto_mqtt);
}

void loop() {
  
static float temperatura = 13.45; // Valor aleatorio, puede ser un pin Analogico.
  
 if (!client.connected()) reconnect();  
      client.loop();
//---- Funcion Publicacion MQTT ----// 
client.publish("miCasa/plantaBaja/habitacion1/temperatura", String(temperatura++).c_str());

delay(5000);
}
