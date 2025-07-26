#include <IRremote.hpp>
#define IR_RECEIVE_PIN 9

const int sw0 = A0;
const int sw1 = A1;
const int LEDS[6] = {2, 3, 4, 5, 6, 7}; 
int bulb = 10;

void setup() {
  Serial.begin(9600);
  pinMode(sw0, INPUT_PULLUP);
  pinMode(sw1, INPUT_PULLUP);

  for (int i = 0; i < 6; i++) {
    pinMode(LEDS[i], OUTPUT);
  }
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  pinMode(bulb, OUTPUT);
}

void loop() {
  int switch0State = digitalRead(sw0);
  int switch1State = digitalRead(sw1);

  int mode = (switch0State == LOW ? 1 : 0) | (switch1State == LOW ? 2 : 0);

  switch (mode) {
    case 0: // 00
      Serial.println("No Connection");
      break;

    case 1: // 01
      Serial.println("IR Connected");
      if (IrReceiver.decode()) {
        if (IrReceiver.decodedIRData.decodedRawData == 0xF30CFF00) {
          Serial.println("1");
          digitalWrite(bulb, LOW);
        }
        else if (IrReceiver.decodedIRData.decodedRawData == 0xE718FF00) {
          Serial.println("2");
          digitalWrite(bulb, HIGH);
        }
        else if (IrReceiver.decodedIRData.decodedRawData == 0xA15EFF00) {
          Serial.println("3");
          digitalWrite(bulb, HIGH);
          for (int i = 0; i < 6; i++) {
            digitalWrite(LEDS[i], HIGH);
            delay(100);
            digitalWrite(LEDS[i], LOW);
            delay(100);
          }
        }
        else if (IrReceiver.decodedIRData.decodedRawData == 0xF708FF00) {
          Serial.println("No Operation");
          digitalWrite(bulb, HIGH);
          for (int i = 0; i < 6; i++) {
            digitalWrite(LEDS[i], LOW);
          }
        }
        IrReceiver.resume();
      }
      break;

    case 2: // 10
      Serial.println("BT Connected");
      if (Serial.available() > 0) {
        char command = Serial.read();
        Serial.println(command);
        switch (command) {
          case '1':
            Serial.println("A");
            delay(500);
            digitalWrite(bulb, LOW);
            break;
          case '2':
            Serial.println("B");
            digitalWrite(bulb, HIGH);
            break;
          case '3':
            Serial.println("C");
            digitalWrite(bulb, HIGH);
            for (int i = 0; i < 6; i++) {
              digitalWrite(LEDS[i], HIGH);
              delay(100);
              digitalWrite(LEDS[i], LOW);
            }
            break;
          case '4':
            Serial.println("No Operation");
            digitalWrite(bulb, HIGH);
            for (int i = 0; i < 6; i++) {
              digitalWrite(LEDS[i], LOW);
            }
            break;
        }
      }
      break;

    case 3: // 11
      Serial.println("No Connection");
      break;
  }
}
