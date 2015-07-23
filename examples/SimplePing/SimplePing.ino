/*
 * With this library an ESP8266 can ping a remote machine and know if it's reachable. 
 * It provides some basic measurements on ping messages (avg response time).
 */

#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>

const char* ssid     = "ssid";
const char* password = "passphrase";

const IPAddress ping_dest(192, 168, 0, 1);

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println("Connecting to WiFi");
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("WiFi connected with ip ");  
  Serial.println(WiFi.localIP());

  if(Ping.ping(ping_dest)) {
    Serial.println("Success!!");
  } else {
    Serial.println("Error :(");
  }
}

void loop() { }
