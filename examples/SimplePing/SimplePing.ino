#include <rdm6300.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ESP8266Ping.h>

const IPAddress remote_ip(185, 22, 67, 79);

#define RDM6300_RX_PIN 13 // can be only 13 - on esp8266 force hardware uart!
#define LOCK_PIN 10
#define LOCK_PIN1 5

Rdm6300 rdm6300;
//Arasan-SPA
// rty19hgw
void setup()
{
	/* Serial1 is the debug! remember to bridge GPIO-01 to GPIO-02 */
	Serial1.begin(115200);

	pinMode(LOCK_PIN, OUTPUT);
	digitalWrite(LOCK_PIN, LOW);
  pinMode(LOCK_PIN1, OUTPUT);
  digitalWrite(LOCK_PIN1, LOW);
  
	rdm6300.begin(RDM6300_RX_PIN);
	Serial1.println("\nPlace RFID tag near the rdm6300...");
  WiFi.begin("Double.office", "Double#1");
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial1.println("Waiting for connection");
 
  }
  Serial1.println("connected");
}


void loop() 
{
	/* get_new_tag_id returns the tag_id of a "new" near tag,
	following calls will return 0 as long as the same tag is kept near. */
	if (rdm6300.get_new_tag_id()) 
  {
		Serial1.println(rdm6300.get_tag_id(), HEX);
    
	/* get_tag_id returns the tag_id as long as it is near, 0 otherwise. */
	//digitalWrite(READ_LED_PIN, rdm6300.get_tag_id());
  if (WiFi.status() == WL_CONNECTED) 
  { //Check WiFi connection status
    Serial1.println(WiFi.status());
    if(Ping.ping(remote_ip, 1))
    {
      Serial1.println("ping succsess");  
      String outString = String("{ \"rfid\": \"") + String(rdm6300.get_tag_id(), HEX) + String("\" }");
      std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
      client->setInsecure();
      HTTPClient http;    //Declare object of class HTTPClient
      Serial1.print("check hhtp client: ");
      
      if (http.begin(*client, "https://arasanspa.kz/api/access/tourniquet/rfid"))
      {   
      Serial1.println(http.begin(*client, "https://arasanspa.kz/api/access/tourniquet/rfid"));
           //Specify request destination
      http.addHeader("Content-Type", "aplication/json");  //Specify content-type header
      
      int httpCode = http.POST(outString);   //Send the request
      Serial1.println(outString);
      String payload = http.getString();                  //Get the response payload
      Serial1.print("http code: ");
      Serial1.println(httpCode);   //Print HTTP return code
      Serial1.println(payload);    //Print request response payload
      
      //http.end();  //Close connection
      if(httpCode >0)
      {

      
        if (payload.equals("true, in")) 
        {
        //Serial1.println(payload);
        digitalWrite(LOCK_PIN, HIGH);
        Serial1.println("unlock");
        delay(500);
        digitalWrite(LOCK_PIN, LOW);
        Serial1.println("lock");
        }
      } else{
          Serial1.println("http conection failed");
          digitalWrite(LOCK_PIN, HIGH);
          Serial1.println("unlock");
          delay(500);
          digitalWrite(LOCK_PIN, LOW);
          Serial1.println("lock");
      }
      }
    }else
      {
          Serial1.println("ping failed");
          digitalWrite(LOCK_PIN, HIGH);
          Serial1.println("unlock");
          delay(500);
          digitalWrite(LOCK_PIN, LOW);
          Serial1.println("lock");
      }
   }
  }
  delay(10);
}
