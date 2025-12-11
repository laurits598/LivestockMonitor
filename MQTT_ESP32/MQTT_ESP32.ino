#include "Secrets.h"
#include <WiFi.h>
#include <esp_wifi.h>
#include <PubSubClient.h>

#define BUZZER_PIN 2 // ESP32

WiFiClient espClient;
PubSubClient client(espClient);

// Callback function to handle incoming messages
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  // Convert payload (byte array) into a String
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  // Check for specific payloads
  if (message == "WARNING") {
    Serial.println("Warning received! Take action here.");
    // e.g., turn on LED, trigger buzzer, etc.
    digitalWrite(BUZZER_PIN, HIGH);
    delay(2000);
    digitalWrite(BUZZER_PIN, LOW);

  }
}

//  If using a ESP32 C3 mini. Does not work tho - C3 is not compatible with MQTT
void setup_wifi_esp32c3() {
  Serial.println("\n--- ESP32-C3 WiFi Test ---");

  WiFi.mode(WIFI_MODE_STA);

  // Disable promiscuous mode
  esp_wifi_set_promiscuous(false);

  // Optional: dummy callback (not used here)
  esp_wifi_set_promiscuous_rx_cb(NULL);

  // Enable promiscuous mode
  esp_wifi_set_promiscuous(true);

  delay(500);

  Serial.print("Connecting to: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
}

void setup_wifi_esp32() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect with username/password
    if (client.connect("ESP32Client", "esp32", "esp32-ok")) {
      Serial.println("connected");
      // Subscribe to topic once connected
      client.subscribe("test/topic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi_esp32();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);   // Register the callback
  pinMode(BUZZER_PIN,OUTPUT);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(500);
  digitalWrite(BUZZER_PIN, LOW);

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();   // Keep MQTT connection alive and process messages
}

