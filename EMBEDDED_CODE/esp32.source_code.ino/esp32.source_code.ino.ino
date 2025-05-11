/*
  ArduinoMqttClient - WiFi Simple Receive + LED Control

  Ce programme se connecte à un broker MQTT et s’abonne à un topic.
  Si le message reçu est "1", il allume la LED connectée au pin 12.
  Si le message est "0", il l’éteint.

  Matériel compatible :
  - Arduino MKR 1000, MKR 1010, Uno WiFi Rev2, ESP32, etc.
*/

#include <ArduinoMqttClient.h>

#if defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_AVR_UNO_WIFI_REV2)
  #include <WiFiNINA.h>
#elif defined(ARDUINO_SAMD_MKR1000)
  #include <WiFi101.h>
#elif defined(ARDUINO_ARCH_ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_NICLA_VISION) || defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_GIGA) || defined(ARDUINO_OPTA)
  #include <WiFi.h>
#elif defined(ARDUINO_PORTENTA_C33)
  #include <WiFiC3.h>
#elif defined(ARDUINO_UNOR4_WIFI)
  #include <WiFiS3.h>
#endif

/////// veuillez entrer vos données sensibles dans arduino_secrets.h
char ssid[] = "Ant";        // nom du réseau WiFi
char pass[] = "88888888";   // mot de passe WiFi

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "broker.emqx.io";
int        port     = 1883;
const char topic[]  = "@lord-nighteyes/led/1/management";

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // attendre la connexion série
  }

  pinMode(12, OUTPUT); // configuration du pin LED

  // Connexion au WiFi
  Serial.print("Connexion au réseau WiFi : ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(5000);
  }
  Serial.println("\nConnecté au WiFi !");
  Serial.println();

  Serial.print("Adresse IP ESP32 : ");
  Serial.println(WiFi.localIP());


  // Connexion au broker MQTT
  Serial.print("Connexion au broker MQTT : ");
  Serial.println(broker);
  if (!mqttClient.connect(broker, port)) {
    Serial.print("Échec de connexion MQTT, code erreur = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }

  Serial.println("Connecté au broker MQTT !");
  Serial.println();

  Serial.print("Abonnement au topic : ");
  Serial.println(topic);
  mqttClient.subscribe(topic);

  Serial.print("En attente des messages sur le topic : ");
  Serial.println(topic);
  Serial.println();
}

void loop() {
  int messageSize = mqttClient.parseMessage();
  if (messageSize) {
    Serial.print("Message reçu sur le topic '");
    Serial.print(mqttClient.messageTopic());
    Serial.print("' (");
    Serial.print(messageSize);
    Serial.println(" octets) :");

    String message = "";
    while (mqttClient.available()) {
      char c = (char)mqttClient.read();
      message += c;
      Serial.print(c);
    }
    Serial.println();
    Serial.println();

    // Contrôle de la LED
    if (message == "1") {
      digitalWrite(12, HIGH); // Allume la LED
      Serial.println("LED allumée.");
    } else if (message == "0") {
      digitalWrite(12, LOW);  // Éteint la LED
      Serial.println("LED éteinte.");
    } else {
      Serial.println("Commande inconnue.");
    }
  }
}
