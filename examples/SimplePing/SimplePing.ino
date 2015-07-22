/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
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
