/* 

Laurits M. Jensen - s194279 

*/

#pragma once
#include <Arduino.h>
#include <Stream.h>
#include <rn2xx3.h>
#include "Config.h"
#include "Utils.h"
#include <SoftwareSerial.h>

//#include "TTN_Config.h"
// Event.h

/* Event-type based approach - not used */
enum class EventType {
    Click,
    Timeout,
    Error,
    Unknown
};

struct Event {
    EventType type;
    // other fields...
};


void downlink(Stream &serialPort, rn2xx3 &myLora);

/* Crucial funcitons for module configuration and connecting to TTN*/
void setDutyCycle(Stream &serialPort, rn2xx3 &myLora);
void initRadio(Stream &serialPort, rn2xx3 &myLora);

/* Setter for "messagesSent" which functions as control-signal - could come in handy for future work */
void setMessagesSent(bool val);

/* Redundant function. Used to send uplink, which can be done with a "one-liner"; <serial>.tx(payload) */
void loraTX(Stream &serialPort, rn2xx3 &myLora, String msg);

String decodeHexToAscii(const String& hexPayload);
String cleanHex(const String& hexPayload);

/* Functions made for a "type"-based approach for downlink messages. The parseEvent classifies them in types.*/
Event parseEvent(const String& payload);
String checkEvent(const Event& e);


void sendTempBytes(rn2xx3 &myLora, float temp);
void sendTempHex(rn2xx3 &myLora);












