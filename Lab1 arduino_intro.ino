//Tinkercad link:  https://www.tinkercad.com/things/jUaVq7IOdzf-street-light-for-adu?sharecode=h8iag45aCy5vI17HOIcSFHdLCP8Tge1xlh2qSKABG0I


//LED + push btn
const int RED_LED = 13;
const int ButtonPin = 2;
int buttonState = 0;

void setup()
{
    pinMode (RED_LED, OUTPUT);
    pinMode (ButtonPin, INPUT);
}

void loop()
{
    buttonState = digitalRead(ButtonPin);
  if(buttonState == HIGH)
  {
    digitalWrite(RED_LED, HIGH);
    delay(1000); 
    digitalWrite(RED_LED, LOW);
    delay(200); 
  }
  else{
    digitalWrite(RED_LED, HIGH);
  }
}



//Stoplight + 7segments
// Pin definitions
const int PinA = 13;
const int PinB = 12;
const int PinC = 11;
const int PinD = 10;
const int PinE = 9;
const int PinF = 8;
const int PinG = 7;
const int PinA1 = A0;
const int PinB1 = A1;
const int PinC1 = A2;
const int PinD1 = A3;
const int PinE1 = A4;
const int PinF1 = 6;
const int PinG1 = 5;

const int RED_LED = 4;
const int ORANGE_LED = 3;
const int GREEN_LED = 2;

// Define durations (in milliseconds)
const unsigned long RED_DURATION = 15000;   // 15 seconds
const unsigned long ORANGE_DURATION = 3000; // 3 seconds
const unsigned long GREEN_DURATION = 25000; // 25 seconds

// Variables to keep track of time
unsigned long startMillis;
unsigned long currentMillis;
unsigned long elapsedMillis;

// Enum to represent traffic light states
enum State { RED, ORANGE, GREEN };

// Current state
State currentState = RED;

// Function prototypes
void changeState(State newState);
void updateCountdown(unsigned long remainingTime);
void displayDigit(int pinA, int pinB, int pinC, int pinD, int pinE, int pinF, int pinG, int digit);
void clearSevenSegment();

void setup() {
  // Initialize LEDs as outputs
  pinMode(RED_LED, OUTPUT);
  pinMode(ORANGE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  // Initialize 7-segment display pins as outputs
  pinMode(PinA, OUTPUT);
  pinMode(PinB, OUTPUT);
  pinMode(PinC, OUTPUT);
  pinMode(PinD, OUTPUT);
  pinMode(PinE, OUTPUT);
  pinMode(PinF, OUTPUT);
  pinMode(PinG, OUTPUT);

  pinMode(PinA1, OUTPUT);
  pinMode(PinB1, OUTPUT);
  pinMode(PinC1, OUTPUT);
  pinMode(PinD1, OUTPUT);
  pinMode(PinE1, OUTPUT);
  pinMode(PinF1, OUTPUT);
  pinMode(PinG1, OUTPUT);

  // Set initial state
  startMillis = millis();
  
  // Start with the red LED on
  digitalWrite(RED_LED, HIGH);
  // Ensure other LEDs are off
  digitalWrite(ORANGE_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
}

void loop() {
  currentMillis = millis();
  elapsedMillis = currentMillis - startMillis;

  switch (currentState) {
    case RED:
      if (elapsedMillis >= RED_DURATION) {
        changeState(ORANGE);
      } else {
        updateCountdown(RED_DURATION - elapsedMillis);
      }
      break;

    case ORANGE:
      if (elapsedMillis >= ORANGE_DURATION) {
        changeState(GREEN);
      } else {
        updateCountdown(ORANGE_DURATION - elapsedMillis);
      }
      break;

    case GREEN:
      if (elapsedMillis >= GREEN_DURATION) {
        changeState(RED);
      } else {
        updateCountdown(GREEN_DURATION - elapsedMillis);
      }
      break;
  }
}

void changeState(State newState) {
  // Turn off all LEDs
  digitalWrite(RED_LED, LOW);
  digitalWrite(ORANGE_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  // Turn off 7-segment displays
  clearSevenSegment();

  // Update state and reset timer
  currentState = newState;
  startMillis = millis();

  // Turn on the appropriate LED
  switch (currentState) {
    case RED:
      digitalWrite(RED_LED, HIGH);
      break;
    case ORANGE:
      digitalWrite(ORANGE_LED, HIGH);
      break;
    case GREEN:
      digitalWrite(GREEN_LED, HIGH);
      break;
  }
}

void updateCountdown(unsigned long remainingTime) {
  int seconds = remainingTime / 1000;
  int tens = seconds / 10;
  int units = seconds % 10;

  // Update first seven-segment display (for tens place)
  displayDigit(PinA, PinB, PinC, PinD, PinE, PinF, PinG, tens);

  // Update second seven-segment display (for units place)
  displayDigit(PinA1, PinB1, PinC1, PinD1, PinE1, PinF1, PinG1, units);
}

void displayDigit(int pinA, int pinB, int pinC, int pinD, int pinE, int pinF, int pinG, int digit) {
  // Define which segments to turn on for each digit (0-9)
  bool segments[10][7] = {
    {true, true, true, true, true, true, false}, // 0
    {false, true, true, false, false, false, false}, // 1
    {true, true, false, true, true, false, true}, // 2
    {true, true, true, true, false, false, true}, // 3
    {false, true, true, false, false, true, true}, // 4
    {true, false, true, true, false, true, true}, // 5
    {true, false, true, true, true, true, true}, // 6
    {true, true, true, false, false, false, false}, // 7
    {true, true, true, true, true, true, true}, // 8
    {true, true, true, true, false, true, true} // 9
  };

  // Turn off all segments
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);

  // Turn on segments for the current digit
  digitalWrite(pinA, segments[digit][0]);
  digitalWrite(pinB, segments[digit][1]);
  digitalWrite(pinC, segments[digit][2]);
  digitalWrite(pinD, segments[digit][3]);
  digitalWrite(pinE, segments[digit][4]);
  digitalWrite(pinF, segments[digit][5]);
  digitalWrite(pinG, segments[digit][6]);
}

void clearSevenSegment() {
  // Turn off all segments on both displays
  digitalWrite(PinA, LOW);
  digitalWrite(PinB, LOW);
  digitalWrite(PinC, LOW);
  digitalWrite(PinD, LOW);
  digitalWrite(PinE, LOW);
  digitalWrite(PinF, LOW);
  digitalWrite(PinG, LOW);

  digitalWrite(PinA1, LOW);
  digitalWrite(PinB1, LOW);
  digitalWrite(PinC1, LOW);
  digitalWrite(PinD1, LOW);
  digitalWrite(PinE1, LOW);
  digitalWrite(PinF1, LOW);
  digitalWrite(PinG1, LOW);
}
