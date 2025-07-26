//With WinForms .NET VS Studio 2022

#include <SPI.h>
#include <MFRC522.h>

// Pin configuration
#define RST_PIN 9    // Reset pin
#define SS_PIN 10    // Slave Select pin
#define Led

MFRC522 rfid(SS_PIN, RST_PIN); // Create an MFRC522 instance

void setup() {
  Serial.begin(9600); // Initialize serial communication
  Serial.println("Initializing RFID Reader...");
  
  SPI.begin();        // Initialize SPI bus
  rfid.PCD_Init();    // Initialize MFRC522 module

  Serial.println("RFID Reader Initialized.");
  Serial.println("Scan an RFID card or tag...");
}

void loop() {
  // Check if a new card is present
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Check if the card can be read
  if (!rfid.PICC_ReadCardSerial()) {
    Serial.println("Error reading card. Please try again.");
    return;
  }

  // Print UID of the card
  Serial.println();
  for (byte i = 0; i < rfid.uid.size; i++) {
    // Print each byte of the UID in hexadecimal format
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "); // Add leading zero for single hex digits
    Serial.print(rfid.uid.uidByte[i], HEX);
  }

  delay(1000);
}
  //Serial.println(); // Move to the next line after printing the UID

  // Print a friendly message
  //Serial.println("Card reading complete!");

  // Halt the card to release it
  //rfid.PICC_HaltA();
  //Serial.println("Card halted. Ready for next scan.");
  //delay(1000); // Delay for a second before allowing the next scan
//}
