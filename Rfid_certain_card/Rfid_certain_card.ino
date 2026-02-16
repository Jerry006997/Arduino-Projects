#include <MFRC522.h> // loads the MFRC522 library (required)
#include <SPI.h> // loads the SPI library so arduino can communicate with the RFID module

int led = 8; // sets led as the name of pin 8 on the arduino board
#define SS_PIN 10 // defines the Arduino pin connected to the MFRC522 SDA/SS pin 
#define RST_PIN 9 // defines what pin the reset pin is 

MFRC522 rfid(SS_PIN, RST_PIN); // creates the MFRC522 reader object using the SS and RST pins

byte allowedUIDLg = 4; // sets allowed UID length to four
byte allowedUID[] = {0x, 0x, 0x, 0x}; // says what the UID should be (put you specific UID here)

void setup() {
  rfid.PCD_Init(); // initializes the MFRC522 reader hardware
  SPI.begin(); // begins SPI
  pinMode(led, OUTPUT); // sets pin 8 as an output
  digitalWrite(led, LOW); // sets pin 8 LOW
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) { // if no new card is detected, exit the loop
    digitalWrite(led, LOW); // sets pin 8 LOW
    return; // exit loop() and let Arduino call it again
  }

  if (!rfid.PICC_ReadCardSerial()) { // if the card’s UID cannot be read, exit the loop
    digitalWrite(led, LOW); // sets pin 8 LOW
    return; // exit loop() and let Arduino call it again
  }

  bool match = true; // sets match to true 
  if (rfid.uid.size != allowedUIDLg) { // if UID size is not equal to 4
    match = false; // sets match to false 
  } else {
    for (byte i = 0; i < allowedUIDLg; i++) { // go through each UID byte
      if (rfid.uid.uidByte[i] != allowedUID[i]) { // if any byte does not match
        match = false; // set match to false 
        break; // break out of the loop
      }
    }
  }

  if (match) { // if the UID matches
    digitalWrite(led, HIGH); // set pin 8 high
    delay(500); // keeps the LED on for half a second
  } else {
    digitalWrite(led, LOW); // set pin 8 Low
  }

  rfid.PICC_HaltA(); // tells the card to stop communicating
  rfid.PCD_StopCrypto1(); // stops encryption on the reader so it can read the next card
}
