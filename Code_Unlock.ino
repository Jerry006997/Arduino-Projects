#include <Servo.h> // Loads the servo library

Servo myServo; // Creates a servo object named myServo
int servo = 3; // Servo signal wire is connected to pin 3

int ledPins[4] = {8,9,10,11}; // LED pins for buttons 1–4
int buttonPins[4] = {4,5,6,7}; // Button pins for buttons 1–4 (using INPUT_PULLUP)

int confirmLed = 12; // LED that lights when the pattern is correct
int denieLed = 13;   // LED that lights when the pattern is wrong
int buzzer = 2;      // Buzzer connected to pin 2
int unlockButton = A0; // Button to exit lockout mode (INPUT_PULLUP)

int correctPattern[4] = {3,1,2,3}; // The required button sequence
int userPattern[4]; // Stores the sequence the user enters
int index = 0; // Tracks how many buttons have been pressed so far

void setup() {
  myServo.attach(servo); // Attach servo to pin 3
  myServo.write(0);      // Start servo at 0 degrees

  // Set LED pins as outputs and button pins as INPUT_PULLUP
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  pinMode(confirmLed, OUTPUT);
  pinMode(denieLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(unlockButton, INPUT_PULLUP);
}

void loop() {
  // Check all 4 buttons; if one is pressed, record it
  for (int i = 0; i < 4; i++){
    if (digitalRead(buttonPins[i]) == LOW) { // LOW = pressed (because of INPUT_PULLUP)
      recordPress(i + 1); // Pass the button number (1–4)
      delay(300); // Debounce + prevent double presses
    }
  }
}

void recordPress(int buttonNumber) {
  // Flash the LED for the button that was pressed
  digitalWrite(ledPins[buttonNumber - 1], HIGH);
  delay(200);
  digitalWrite(ledPins[buttonNumber - 1], LOW);

  // Store the button number in the user pattern
  userPattern[index] = buttonNumber;
  index++; // Move to next slot

  // If 4 buttons have been pressed, check the pattern
  if (index == 4) {
    checkPattern();
  }
}

void checkPattern() {
  bool correct = true; // Assume correct until proven wrong

  // Compare user pattern to correct pattern
  for (int i = 0; i < 4; i++) {
    if (userPattern[i] != correctPattern[i]) {
      correct = false;
    }
  }

  if (correct) {
    // Correct pattern feedback
    digitalWrite(confirmLed, HIGH);
    myServo.write(90);

    tone(buzzer, 800);  delay(500);
    tone(buzzer, 1000); delay(500);
    tone(buzzer, 1300); delay(100);
    tone(buzzer, 900);  delay(100);
    tone(buzzer, 1300); delay(1000);
    noTone(buzzer);

    lockout(); // Enter lockout mode
  } else {
    // Wrong pattern feedback
    digitalWrite(denieLed, HIGH);
    tone(buzzer, 800);
    delay(1000);
    noTone(buzzer);

    lockout(); // Enter lockout mode
  }
}

void lockout() {
  // Stay locked until unlockButton is pressed
  while(true) {
    if (digitalRead(unlockButton) == LOW){
      delay(200); // Debounce
      resetPattern();
      return; // Exit lockout
    }
  }
}

void resetPattern() {
  index = 0; // Reset input index
  digitalWrite(confirmLed, LOW);
  digitalWrite(denieLed, LOW);
  myServo.write(0); // Reset servo to locked position
}
