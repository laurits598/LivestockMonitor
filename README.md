
# Authorship
This README—including all documentation, diagrams, explanations, and descriptions of the Livestock Monitor system—was written by Laurits M. Jensen. All code, configurations, and system descriptions presented here are authored by me unless otherwise noted.
Regarding the UI, the backend is also responsible for hosting and creating the pipeline for the UI design as part of my contribution.
A separate folder in this repository contains the contributions of the other group members, each with their own README files documenting their respective work.

# Livestock Monitor Prototype
![Fritzing Schematic of the setup](images/total-setup-fritzing.png)

## Pin Connections


### RN2483 Module → Arduino Pro Mini

| RN2483 Pin    | Arduino Pin                    | Notes                                |
| ------------- | ------------------------------ | ------------------------------------ |
| **TX**        | **D10 (RX-in on Arduino)**     | LoRa → Arduino (serial data)         |
| **RX**        | **D11 (TX-out on Arduino)**    | Arduino → LoRa                       |
| **3V3**       | **VCC**                        | Powered by Arduino 3.3V rail         |
| **GND**       | **GND**                        | Common ground                        |
| **RST**       | **Not connected** or tied high | (Based on diagram: RST is not wired) |
| **CTS / RTS** | **Not connected**              | Hardware flow control unused         |


### Temperature Sensor → Arduino Pro Mini (Voltage Divider)

| Component / Pin       | Arduino Pin | Notes |
|-----------------------|-------------|-------|
| Sensor left pin       | VCC         | Sensor supply voltage |
| Sensor right pin      | → Resistor  | Forms voltage divider |
| Resistor (10K) left   | A0          | Analog input reads divider voltage |
| Resistor (10K) right  | GND         | Divider reference ground |

---


# ESP32 Alert System (Base station)

<img src="images/basestation-setup.png" width="500">

## Pin Connections

### Buzzer & LED → ESP32

| Component | Pin / Connection          | ESP32 Pin / Notes                     |
|-----------|----------------------------|----------------------------------------|
| **Buzzer** | S                          | D23 — Signal control                   |
|           | +                          | 3V3 — Power                            |
|           | –                          | GND — Ground                           |
| **LED**    | Anode (+)                  | D22 — LED control pin                  |
|           | Cathode (–) → Resistor 1k → | GND — Current-limiting resistor needed |

---

# Codebase Structure of the IoT devices
## Livestock Monitor
### File tree-structure of the LoRaWAN_LivestockMonitor project
<pre>
LoRaWAN_LivestockMonitor.ino/
│
├── LoRaWAN_LivestockMonitor.ino
│
├── Accelerator.cpp
├── Accelerator.h
│
├── Config.h
│
├── GPS.cpp
├── GPS.h
│
├── PNP_Management.cpp
├── PNP_Management.h
│
├── RN2483.cpp
├── RN2483.h
│
├── TTN_Config.h
│
├── Utils.cpp 
└── Utils.h
</pre>

### Brief file description
Only seven files are active in the current prototype stage, which are; the main sketch (*.ino), RN2483 and Accelerator modules, Config library and the TTN_Config library. The Utils modules contains unused helper functions, and the remaining files haven't been implemented yet.
### Used libraries 
##### rn2xx3.h
<pre> 
Author: JP Meijers 
Version: Varies by release 
Docs: https://github.com/jpmeijers/RN2483-Arduino 
</pre>

##### SoftwareSerial.h
<pre> 
Author: Arduino 
Version: Part of the Arduino AVR core 
Docs: https://www.arduino.cc/reference/en/language/functions/communication/serial/softwareserial/ 
</pre>

##### Arduino.h
<pre> 
Author: Arduino 
Version: Core Arduino API header 
Docs: https://www.arduino.cc/reference/en/ 
</pre>

##### Stream.h
<pre> 
Author: Arduino 
Version: Part of the Arduino core (abstract stream interface) 
Docs: https://www.arduino.cc/reference/en/language/functions/communication/stream/ 
</pre>


## ESP32 base station
### File tree-structure of the LoRaWAN_LivestockMonitor project
<pre>
LoRaWAN_LivestockMonitor.ino/
│
├── LoRaWAN_LivestockMonitor.ino
│
└── Secrets.h
</pre>
### Brief file description
The ESP32 has an almost monotholic file structure, meaning its codebase is not subdivided into cpp/h modules. It contains one extra library file, which only purpose is to store sensitive credentials.
### Used libraries 
##### WiFi.h
<pre>
Author: Espressif Systems
Version: Part of the ESP32 Arduino Core
Docs: https://docs.espressif.com/projects/arduino-esp32/en/latest/api/wifi.html
</pre>

##### esp_wifi.h
<pre>
Author: Espressif Systems
Version: Part of the ESP-IDF (ESP32 SDK)
Docs: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_wifi.html
</pre>

##### PubSubClient.h
<pre>
Author: Nick O’Leary
Version: 2.8
Docs: http://pubsubclient.knolleary.net/api
</pre>

# Backend 
## Server-sided scripts
### TTN payload-formatter
The TTN payload formatter is written in javascript, and can be configured in the TTN console. The one used in this project can be found in the CloudPipeline directory, decodes the uplink messages and assemble them in a specific format. For this pipeline to work, its crucial that this format is kept. The Azure-hosted listener looks for this specific format, which is <flag>:<event>.


### TTN evnt listener running on Azure-hosted Virtual Machine
The TTN event listener is a Python script running on an Azure-hosted Virtual Machine. It monitors the TTN dataflow in real time and inspects incoming payloads for specific flags generated by the livestock device. When the appropriate flag is detected, the script triggers a warning event, which is published via MQTT to the ESP32 base station. The listener uses Azure libraries to interface with the IoT Hub, forming a pipeline between TTN → Azure IoT Hub → Virtual Machine. Libraries needed to run the listener can be found in requirements.txt. 

