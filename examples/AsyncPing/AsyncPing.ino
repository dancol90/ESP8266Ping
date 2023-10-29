/*
 * This example show how to ping a remote machine using it's hostname asynchrounously
 */

#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>

const char* ssid     = "ssid";
const char* password = "passphrase";

const char* remote_host = "www.google.com";

void setup()
{
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println("Connecting to WiFi");
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("WiFi connected with ip ");  
  Serial.println(WiFi.localIP());

  Serial.print("Pinging host ");
  Serial.println(remote_host);

  if(Ping.ping(remote_host, 5, true))
  {
    Serial.println("Ping is running!!");
  } else
  {
    Serial.println("Ping is not running :(");
  }
}

void loop()
{

  // check if ping has a result (and reset the result flag)
  if (Ping.hasResult(true)) {

    bool ret = Ping.hasSuccess();

    int avg_time_ms = Ping.averageTime();
    int min_time_ms = Ping.minTime();
    int max_time_ms = Ping.maxTime();

    // ...
  }

  // do something else 
  delay(100);

}
