/* 

Laurits M. Jensen - s194279 

*/


#include "RN2483.h"
#include "TTN_Config.h"
bool messagesSent = false;  // Can't be put in *.h since *.h is called here and in *.ino; Error - defined twice

//const char *devAddr = "02017201";
//const char *nwkSKey = "6BC0EA87D08472B1A82D0476C1F85D36";
//const char *appSKey = "E057544428F0BB294C93A0E874EB2A13";
//
//const char *appEui = "0000000000000000";
//const char *appKey = "6B9511F01BA522A813AA85B462190564";

/*
When you call from "*.ino" mySerial map to serialPort

The instance-name serialPort is surprisingly annoying to look at, but got it from chatGPT while struggling with parsing SoftWareSerial objects
from the *.ino file to *.cpp files. The solution included passing parameters as base-class references in order to enable polymorphism. 
Hence every function has multiple mentions of "serialPort". 

*/

void downlink(Stream &serialPort, rn2xx3 &myLora) {

  uint8_t txBuffer[] = {0x1a, 0x06, 0x5b, 0x0a, 0x5b, 0xbb};
  uint8_t incomingByte;  // <-- Add this line

  Serial.println("TXing");
  int result = myLora.txBytes(txBuffer, sizeof(txBuffer)); //one byte, blocking function
  
  Serial.print("Received: ");
  while (serialPort.available() > 0) {
    incomingByte = serialPort.read();
    Serial.write(incomingByte);
  }

  switch(result) //one byte, blocking function
  {
    case TX_FAIL:
    {
      Serial.println("TX unsuccessful or not acknowledged");
      break;
    }
    case TX_SUCCESS:
    {
      Serial.println("TX successful and acknowledged");
      break;
    }
    case TX_WITH_RX: 
    {
      String hexPayload = myLora.getRx();
      cleanHex(hexPayload);
      break;
    }

    default:
    {
      Serial.println("Unknown response from TX function");
    }
  }
  delay(20000);

}

void setDutyCycle(Stream &serialPort, rn2xx3 &myLora) {
  Serial.println("Successfully joined TTN");
  myLora.setDR(0);  //Setting to SF12

  // Setting duty cycle to 10% for all channels
  String str;

  serialPort.println("mac set ch dcycle 1 9");
  str = serialPort.readStringUntil('\n');
  Serial.print("I received: ");
  Serial.println(str);

  serialPort.println("mac set ch dcycle 2 9");
  str = serialPort.readStringUntil('\n'); 
  Serial.print("I received: ");
  Serial.println(str);

  serialPort.println("mac set ch dcycle 3 9");
  str = serialPort.readStringUntil('\n');
  Serial.print("I received: ");
  Serial.println(str);

  myLora.setDR(5);  //Setting SF to SF7

}

void initRadio(Stream &serialPort, rn2xx3 &myLora) {
  //reset rn2483
  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, LOW);
  delay(500);
  digitalWrite(RESET_PIN, HIGH);

  delay(100); //wait for the RN2xx3's startup message
  serialPort.flush();

  //Autobaud the rn2483 module to 9600. The default would otherwise be 57600.
  myLora.autobaud();

  //check communication with radio
  String hweui = myLora.hweui();
  while(hweui.length() != 16)
  {
    //Serial.println("Communication with RN2xx3 unsuccessful. Power cycle the board.");
    //Serial.println(hweui);
    delay(10000);
    hweui = myLora.hweui();
  }

  //print out the HWEUI so that we can register it via ttnctl
  Serial.println("When using OTAA, register this DevEUI: ");
  Serial.println(myLora.hweui());
  Serial.println("RN2xx3 firmware version:");
  Serial.println(myLora.sysver());

  //configure your keys and join the network
  Serial.println("Trying to join TTN");
  bool join_result = false;


  
  join_result = myLora.initABP(devAddr, appSKey, nwkSKey);

  
  join_result = myLora.initOTAA(appEui, appKey);


  while(!join_result)
  {
    //Serial.println("Unable to join. Are your keys correct, and do you have TTN coverage?");
    delay(60000); //delay a minute before retry
    join_result = myLora.init();
  }
  Serial.println("Successfully joined TTN");



}

void setMessagesSent(bool val) {
  messagesSent = val;
}

void loraEventTX(Stream &serialPort, rn2xx3 &myLora, int event) {
  
  if (event == 1) {
    String payload = "";
    Serial.println("Event 1 sent");
  }
  else if (event == 2) {
    String payload = "";
    Serial.println("Event 2 sent");
  }
  else if (event == 3) {
    String payload = "";
    Serial.println("Event 3 sent");
  } 
  
  led_on();

  String payload = "";
  myLora.tx(payload);
  serialPort.println("TXing");
  delay(1000);
  
  setMessagesSent(true);
  digitalWrite(ledPin, HIGH);

}

String cleanHex(const String& hexPayload){
  String decoded = decodeHexToAscii(hexPayload);
  for (int i = 0; i < decoded.length(); i++) {
      byte b = decoded[i];
      Serial.print("Index ");
      Serial.print(i);
      Serial.print(": value=");
      Serial.print(b);
      Serial.print(" char='");
      if (isPrintable(b)) Serial.print((char)b);
      else Serial.print('.');
      Serial.println("'");
  }

  String clean;
  for (int i = 0; i < decoded.length(); i++) {
      char c = decoded[i];
      if (isPrintable(c)) {
          clean += c;
      }
  }
  Serial.println("Cleaned string: " + clean);

  return clean;

}

String decodeHexToAscii(const String& hexPayload) {
    String result;
    for (int i = 0; i < hexPayload.length(); i += 2) {
        String byteStr = hexPayload.substring(i, i+2);
        char c = (char) strtol(byteStr.c_str(), nullptr, 16);
        result += c;
    }
    return result;
}



// Intended as primary uplink function
void loraTX(Stream &serialPort, rn2xx3 &myLora, String msg) {
  led_on();

  String payload = "";
  myLora.tx(payload);
  serialPort.println("TXing");
  delay(1000);
  
  setMessagesSent(true);
  digitalWrite(ledPin, HIGH);

}

/* Not used; parseEvent, checkEvent*/

Event parseEvent(const String& payload) {
    if (payload == "Click")   return {EventType::Click};
    if (payload == "Timeout") return {EventType::Timeout};
    if (payload == "Error")   return {EventType::Error};
    return {EventType::Unknown};
}

String checkEvent(const Event& e) {
    switch (e.type) {
        case EventType::Click:
            return "Click handled";
        case EventType::Timeout:
            return "Timeout handled";
        case EventType::Error:
            return "Error handled";
        default:
            return "Unknown event";
    }
}


/* --  OBS: FUNCTIONS BELOW
Mixture of online copy-paste + partially chatGPT-gen functions. 

Kept here as they took part in debugging of flawed serial output 

Only used for debugging, and doesn't take active part in the embedded design 

These helper functions should be moved to Utils.
-- */

// Cleans the decoded hex string from random bs characters 

void sendTempBytes(rn2xx3 &myLora, float temp) {
    uint8_t dataArray[sizeof(float)];

    // Copy float into byte array
    memcpy(dataArray, &temp, sizeof(float));

    // Debug print
    Serial.print("TX buffer: ");
    for (size_t i = 0; i < sizeof(float); i++) {
        Serial.print(dataArray[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    // Send over LoRa
    myLora.txBytes(dataArray, sizeof(dataArray));
}

void sendTempHex(rn2xx3 &myLora) {
  uint8_t txBuffer[] = {0x1a};
  myLora.txBytes(txBuffer, sizeof(txBuffer));
  //delay(60000);
}

















