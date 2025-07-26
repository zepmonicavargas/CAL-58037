//Running + blinking lights

const int sw0 = A0;
const int sw1 = A1;
const int LEDS[6] = {2, 3, 4, 5, 6, 7}; 

void setup() {
  pinMode(sw0, INPUT_PULLUP);
  pinMode(sw1, INPUT_PULLUP);

  for (int i = 0; i < 6; i++) {
    pinMode(LEDS[i], OUTPUT);
  }
}

void loop() {
  int switch0State = digitalRead(sw0);
  int switch1State = digitalRead(sw1);

  int mode = (switch0State == LOW ? 1 : 0) | (switch1State == LOW ? 2 : 0);

  switch (mode) {
    case 0: // 00
      for (int i = 0; i < 6; i++) {
        digitalWrite(LEDS[i], HIGH);
      }
      break;

    case 1: // 01
      for (int i = 0; i < 6; i++) {
        digitalWrite(LEDS[i], HIGH);
        delay(100);
        digitalWrite(LEDS[i], LOW);
      }
      break;

    case 2: // 10
      for (int i = 5; i >= 0; i--) {
        digitalWrite(LEDS[i], HIGH);
        delay(100);
        digitalWrite(LEDS[i], LOW);
      }
      break;

    case 3: // 11
      int pattern[6][6] = {
        {1, 0, 0, 0, 0, 1}, 
        {0, 1, 0, 0, 1, 0}, 
        {0, 0, 1, 1, 0, 0},
        {0, 0, 1, 1, 0, 0}, 
        {0, 1, 0, 0, 1, 0}, 
        {1, 0, 0, 0, 0, 1}  
      };

      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
          digitalWrite(LEDS[j], pattern[i][j] ? HIGH : LOW);
        }
        delay(100);
      }

      for (int i = 5; i >= 0; i--) {
        for (int j = 0; j < 6; j++) {
          digitalWrite(LEDS[j], pattern[i][j] ? HIGH : LOW);
        }
        delay(100);
      }
      break;
  }
}
