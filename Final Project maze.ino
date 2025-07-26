//Maze Game with WinForms .NET VS Studio 2022

#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <avr/wdt.h>

const int joystickXPin = A0;             // X-axis joystick (left-right)
const int joystickYPin = A1;             // Y-axis joystick (up-down)
const int servo1Pin = 6;                 // Servo 1 control pin (left-right)
const int servo2Pin = 5;                 // Servo 2 control pin (up-down)
const int startButtonPin = 7;            // Start Button
const int resetButtonInterruptPin = 2;   // Reset Button
const int easyButtonPin = 9;             // Easy Button
const int mediumButtonPin = 10;          // Medium Button
const int hardButtonPin = 11;            // Hard Button
const int trigPin = 12;                  // Ultrasonic sensor trigger pin
const int echoPin = 13;                  // Ultrasonic sensor echo pin

Servo servo1;
Servo servo2;

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Countdown variables
int countdownEasy = 45;           // Start countdown at 45 seconds
int countdownMed = 30;            // Start countdown at 30 seconds
int countdownHard = 15;           // Start countdown at 15 seconds
unsigned long gameStartTime = 0;  // Timer to track the game duration
bool gameRunning = false;
bool gameStartedEasy = false;
bool gameRunning1 = false;
bool gameStartedMed = false;
bool gameRunning2 = false;
bool gameStartedHard = false;
unsigned long previousMillis = 0; // For non-blocking timer
const unsigned long interval = 1000; // 1-second interval
bool startButtonPrevState = HIGH;
bool resetButtonPrevState = HIGH;
bool easyButtonPrevState = HIGH;
bool mediumButtonPrevState = HIGH;
bool hardButtonPrevState = HIGH;

long duration;
int distance;

void resetArduino() {
  wdt_enable(WDTO_15MS); // Enable watchdog timer to reset Arduino
  while (true) {
    // Wait for the watchdog timer to trigger the reset
  }
}
void setup() {
  // Initialize the servo motors

  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(resetButtonInterruptPin, INPUT_PULLUP);
  pinMode(easyButtonPin, INPUT_PULLUP);
  pinMode(mediumButtonPin, INPUT_PULLUP);
  pinMode(hardButtonPin, INPUT_PULLUP);
  pinMode(trigPin, OUTPUT);  // Ultrasonic trigger
  pinMode(echoPin, INPUT);   // Ultrasonic echo

  attachInterrupt(digitalPinToInterrupt(resetButtonInterruptPin), resetArduino, FALLING);

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Welcome to");
  lcd.setCursor(3,1);
  lcd.print("MAZE GAME!");
  
  // Start serial communication (optional for debugging
  Serial.begin(9600);
}
long measureDistance() {
  // Send a 10-microsecond pulse to the trig pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in cm
  long distance = duration * 0.034 / 2;

  return distance;
}
void interruptGameIfDistanceEquals3() {
  long distance = measureDistance();

  // Check if the distance equals 3
  if (distance != 0 && distance <= 4) {
    Serial.write('6');
    //Serial.println("6");
    gameStartedEasy = false;
    gameStartedMed = false;
    gameStartedHard = false;

    // Display "Interrupted" on the LCD
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Finished!");
    delay(2000);
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("You Won!");
    delay(2000);
    resetArduino();
    // Optionally, you could reset the game or halt operations here
  }
}
void displayEasy() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval && countdownEasy >= 0) {
    previousMillis = currentMillis; // Reset the timer

    // Update the countdown on the LCD
    lcd.setCursor(0, 1);
    lcd.print("         "); // Clear the line
    lcd.setCursor(0, 1);
    lcd.print(countdownEasy);

    // Decrement the countdown
    countdownEasy--;

    if (countdownEasy < 0) {
      lcd.setCursor(0, 1);
      lcd.print("0");
    }
  }
}
void displayMed() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval && countdownMed >= 0) {
    previousMillis = currentMillis; // Reset the timer

    // Update the countdown on the LCD
    lcd.setCursor(0, 1);
    lcd.print("         "); // Clear the line
    lcd.setCursor(0, 1);
    lcd.print(countdownMed);

    // Decrement the countdown
    countdownMed--;

    if (countdownMed < 0) {
      lcd.setCursor(0, 1);
      lcd.print("0");
    }
  }
}
void displayHard() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval && countdownHard >= 0) {
    previousMillis = currentMillis; // Reset the timer

    // Update the countdown on the LCD
    lcd.setCursor(0, 1);
    lcd.print("         "); // Clear the line
    lcd.setCursor(0, 1);
    lcd.print(countdownHard);

    // Decrement the countdown
    countdownHard--;

    if (countdownHard < 0) {
      lcd.setCursor(0, 1);
      lcd.print("0");
    }
  }
}

void joystick() {
  // Read the joystick positions
  int joystickX = analogRead(joystickXPin);  // Read X axis (left-right)
  int joystickY = analogRead(joystickYPin); // Read Y axis (up-down)

  // Map the joystick input to servo motor angles (0 to 180 degrees)
  int servo1Angle = map(joystickX, 0, 1023, 0, 180); // Map X axis to servo1
  int servo2Angle = map(joystickY, 0, 1023, 0, 180); // Map Y axis to servo2

  // Set the servo positions
  servo1.write(servo1Angle);
  servo2.write(servo2Angle);

  // Optional: Print joystick and servo angles to serial monitor for debugging
  //Serial.print("Joystick X: ");
  //Serial.print(joystickX);
  //Serial.print(" | Servo1 Angle: ");
  //Serial.print(servo1Angle);
  //Serial.print(" | Joystick Y: ");
  //Serial.print(joystickY);
  //Serial.print(" | Servo2 Angle: ");
  //Serial.println(servo2Angle);

  // Small delay to reduce jitter
  delay(10); // Adjust this delay for smoother joystick movement
}
void loop() {

  
 bool startButtonState = digitalRead(startButtonPin);
 //bool resetButtonState = digitalRead(resetButtonPin);

  // Check for "Start Button" press
  if ((startButtonPrevState == HIGH && startButtonState == LOW) || (Serial.available() && Serial.read() == '1')) {
    Serial.println("Start Button Pressed");
    lcd.setCursor(0, 0);
    lcd.print("Select Difficulty");
    lcd.setCursor(0, 1);
    lcd.print("Easy/Medium/Hard");

    while (true) {
      bool easyButtonState = digitalRead(easyButtonPin);
      bool mediumButtonState = digitalRead(mediumButtonPin);
      bool hardButtonState = digitalRead(hardButtonPin);
      char receivedChar = 0; // Initialize a variable to store the serial input
      if (Serial.available()) {
      receivedChar = Serial.read(); // Read the serial input and store it
    }
      
      if ((easyButtonState == LOW) || (receivedChar == '2')) { // Easy button pressed
        Serial.println("Easy Button Pressed");
        for (int i = 3; i >= 1; i--) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("[Easy] ready in:");
          lcd.setCursor(0, 1);
          lcd.print(i);
          delay(1000); // Wait for 1 second before updating
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("[Easy] ready in:");
        lcd.setCursor(0, 1);
        lcd.print("GO!");
        delay(1000); 

        lcd.clear();
        gameStartTime = millis();
        gameStartedEasy = true;

        // Exit the difficulty selection loop
        break;
      }

      else if ((mediumButtonState == LOW) || (receivedChar == '3')) { // Medium button pressed
        Serial.println("Medium Button Pressed");
        for (int i = 3; i >= 1; i--) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("[Medium] ready in:");
          lcd.setCursor(0, 1);
          lcd.print(i);
          delay(1000); // Wait for 1 second before updating
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("[Medium] ready in:");
        lcd.setCursor(0, 1);
        lcd.print("GO!");
        delay(1000); 

        lcd.clear();
        gameStartTime = millis();
        gameStartedMed = true;

        // Exit the difficulty selection loop
        break;
      }

      else if ((hardButtonState == LOW) || (receivedChar == '4')) { // Hard button pressed
        Serial.println("Hard Button Pressed");
        for (int i = 3; i >= 1; i--) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("[Hard] ready in:");
          lcd.setCursor(0, 1);
          lcd.print(i);
          delay(1000); // Wait for 1 second before updating
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("[Hard] ready in:");
        lcd.setCursor(0, 1);
        lcd.print("GO!");
        delay(1000); 

        lcd.clear();
        gameStartTime = millis();
        gameStartedHard = true;

        break;
     }
      else if (receivedChar == '5'){
        startButtonState == LOW;
        lcd.begin(16, 2);
        lcd.backlight();
        lcd.setCursor(3, 0);
        lcd.print("Welcome to");
        lcd.setCursor(3,1);
        lcd.print("MAZE GAME!");
        break;
    }
}
  }
  if (gameStartedEasy) {
    interruptGameIfDistanceEquals3();
    unsigned long currentMillis = millis();
    
    if (currentMillis - gameStartTime < 48500) {
      displayEasy();
      joystick();
    } else {
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("You Lose!");
      
      // Optionally, you could reset the game here if needed
      gameStartedEasy = false;  // Stop the game loop
      delay(1000);
      wdt_enable(WDTO_15MS); // Set the watchdog timer to 15ms
        while (true) {
            // Wait for the watchdog timer to reset the Arduino
        }
    }
  }
  if (gameStartedMed) {
    interruptGameIfDistanceEquals3();
    unsigned long currentMillis = millis();
    
    if (currentMillis - gameStartTime < 36500) {
      displayMed();
      joystick();
    } else {
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("You Lose!");
      
      // Optionally, you could reset the game here if needed
      gameStartedMed = false;  // Stop the game loop
      delay(1000);
      wdt_enable(WDTO_15MS); // Set the watchdog timer to 15ms
        while (true) {
            // Wait for the watchdog timer to reset the Arduino
        }
    }
  }
  if (gameStartedHard) {
    interruptGameIfDistanceEquals3();
    unsigned long currentMillis = millis();
    
    if (currentMillis - gameStartTime < 17000) {
      displayHard();
      joystick();
    } else {
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("You Lose!");
      
      // Optionally, you could reset the game here if needed
      gameStartedHard = false;  // Stop the game loop
      delay(1000);
      wdt_enable(WDTO_15MS); // Set the watchdog timer to 15ms
        while (true) {
            // Wait for the watchdog timer to reset the Arduino
        }
    }
  }

  // Check for "Reset Button" press
 /* else if (resetButtonPrevState == HIGH && resetButtonState == LOW) {
    Serial.println("Reset Button Pressed");
    // Add your condition handling code for Reset here
  }*/

  // Update button states for the next loop iteration
  startButtonPrevState = startButtonState;
  //resetButtonPrevState = resetButtonState;*/
}
