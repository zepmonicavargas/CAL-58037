//With WinForms .NET VS Studio 2022

int speed = 255;

void setup() {
    pinMode(8, OUTPUT);  // Left motor direction
    pinMode(9, OUTPUT);  // Left motor speed
    pinMode(10, OUTPUT); // Right motor speed
    pinMode(11, OUTPUT); // Right motor direction
    pinMode(7, OUTPUT);  // Buzzer
    Serial.begin(9600);  // Start serial communication for Bluetooth
}

void loop() {
    if (Serial.available() > 0) {
        char command = Serial.read();  // Read the command from Bluetooth
        Serial.println(command);

        if (command == 'F') {
            // Move forward
            digitalWrite(8, HIGH);  // Set direction forward for left motor
            digitalWrite(11, HIGH); // Set direction forward for right motor
            analogWrite(9, speed);  // Left motor speed
            analogWrite(10, speed); // Right motor speed
            delay(10);
            
        } 
        else if (command == 'B') {
            // Move backward
            digitalWrite(8, LOW);   // Set direction backward for left motor
            digitalWrite(11, LOW);  // Set direction backward for right motor
            analogWrite(9, speed);
            analogWrite(10, speed);
            delay(10);
          
        } 
        else if (command == 'L') {
            // Turn right
            digitalWrite(8, HIGH);  // Forward for left motor
            digitalWrite(11, LOW);  // Backward for right motor
            analogWrite(9, 200);    // Set left motor to speed 200
            analogWrite(10, 200);   // Set right motor to speed 200
            delay(10);
        } 
        else if (command == 'R') {
            // Turn left
            digitalWrite(8, LOW);   // Backward for left motor
            digitalWrite(11, HIGH); // Forward for right motor
            analogWrite(9, 200);
            analogWrite(10, 200);
            delay(10);
        }
        else if (command == 'I') {
            // Forward left
            digitalWrite(8, HIGH);  // Forward for left motor
            digitalWrite(11, HIGH); // Forward for right motor
            analogWrite(9, speed / 2);  // Half speed for left motor
            analogWrite(10, speed);     // Full speed for right motor
            delay(10);
        }
        else if (command == 'G') {
            // Forward right
            digitalWrite(8, HIGH);  // Forward for left motor
            digitalWrite(11, HIGH); // Forward for right motor
            analogWrite(9, speed);     // Full speed for left motor
            analogWrite(10, speed / 2); // Half speed for right motor
            delay(10);
        }
        else if (command == 'J') {
            // Backward left
            digitalWrite(8, LOW);   // Backward for left motor
            digitalWrite(11, LOW);  // Backward for right motor
            analogWrite(9, speed / 2);  // Half speed for left motor
            analogWrite(10, speed);     // Full speed for right motor
            delay(10);
        }
        else if (command == 'H') {
            // Backward right
            digitalWrite(8, LOW);   // Backward for left motor
            digitalWrite(11, LOW);  // Backward for right motor
            analogWrite(9, speed);     // Full speed for left motor
            analogWrite(10, speed / 2); // Half speed for right motor
            delay(10);
        }
        else if (command == 'V') {
            // Turn on buzzer
            digitalWrite(7, HIGH);  // Buzzer on
        }
        else if (command == 'v') {
            // Turn off buzzer
            digitalWrite(7, LOW);   // Buzzer off
        }

        // Stop the motors after the command completes
        analogWrite(9, 0);
        analogWrite(10, 0);
    }
}
