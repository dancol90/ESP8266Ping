
#ifndef ESP826Ping_H
#define ESP826Ping_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

extern "C" {
  #include <ping.h>
}

//#define DEBUG_PING(...) Serial.printf(__VA_ARGS__)
#define DEBUG_PING(...)

class PingClass {
  public:
    PingClass();

    bool ping(IPAddress dest, byte count = 5);

    int averageTime();

  protected:
    static void _ping_sent_cb(void *opt, void *pdata);
    static void _ping_recv_cb(void *opt, void *pdata);

    IPAddress _dest;
    ping_option _options;

    static byte _expected_count, _errors, _success;
    static int _avg_time;
};

extern PingClass Ping;

#endif
