
### File tree-structure of the Arduino Project Sketch.

TTN_Connect_V2/
│
├── TTN_Connect_V2.ino
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



![Fritzing Schematic of the setup](images/total-setup-fritzing.png)

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




# Pin Connections




## RN2483 → Arduino Pro Mini
TX  => D10  
RX  => D11  
3V3 => VCC  
GND => GND  
RST => D7  
CTS => (not connected)  
RTS => (not connected)

---

## MPU6050 → Arduino Pro Mini
VCC => VCC  
GND => GND  
SCL => A5  
SDA => A4  
INT => (not connected)  
XDA => (not connected)  
XCL => (not connected)

---
## Temperature Sensor → Arduino Pro Mini
# Voltage divider setup
Left pin   => VCC  
Right pin  => Resistor(10K)  

Resistor → Arduino Pro Mini
Left pin   => A0  
Right pin  => GND 

---

## Shared Rails
Red rail  => VCC  
Blue rail => GND



## ESP32 Alert System (Base station)

![Fritzing Schematic of the setup](images/basestation-setup.png)

# Pin Connections

## Buzzer → ESP32
S  => D23  
+  => 3V3  
-  => GND  

---

## LED → ESP32
LED Anode   (+) => D22  
LED Cathode (–) => Resistor(1k) => GND

---

## Shared Rails
Red rail  => 3V3  
Blue rail => GND










