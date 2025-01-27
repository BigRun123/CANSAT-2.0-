// Feather9x_TX
// -*- mode: C++ -*-
// Example sketch showing how to filter incoming messages to only display specific data on the serial monitor.
 
#include <SPI.h>
#include <RH_RF95.h>
 
#define RFM95_CS    8
#define RFM95_INT   7
#define RFM95_RST   4
 
// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 433.0
 
// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);
 
void setup() {
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
 
  Serial.begin(115200);
  while (!Serial) delay(1);
  delay(100);
 
  Serial.println("Feather LoRa TX Test!");
 
  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
 
  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  Serial.println("LoRa radio init OK!");
 
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
 
  rf95.setTxPower(23, false);
}
 
void loop() {
  delay(1000); // Wait 1 second between transmits
 
  // Now wait for incoming messages
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  Serial.println(sizeof(buf));
  Serial.println("Waiting for incoming message...");
  if (rf95.waitAvailableTimeout(1000)) {
    if (rf95.recv(buf, &len)) {
      buf[len] = 0;  // Null-terminate the received string
      String message = String((char *)buf);
      Serial.println(sizeof(message));
      Serial.println(message);
 
      if (message.startsWith("4")) {  // Filter for specific messages
        Serial.print("Accepted message: ");
        Serial.println(message);
        Serial.print("RSSI: ");
        Serial.println(rf95.lastRssi(), DEC);
 
        char radiopacket[20] = "8Hello World";  // Message to transmit
        Serial.print("Sending: "); Serial.println(radiopacket);
 
        rf95.send((uint8_t *)radiopacket, strlen(radiopacket));
        rf95.waitPacketSent();
 
      } else {
      }
    } else {
      Serial.println("Receive failed");
    }
  } else {
    Serial.println("No message received within timeout");
  }
}
