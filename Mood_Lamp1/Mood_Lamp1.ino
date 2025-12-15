// Define the pins for the RGB LED
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

// Define variables to hold the current color values
int redValue = 255;
int greenValue = 0;
int blueValue = 0;

void setup() {
  // Set the RGB LED pins as output
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // Fade from red to green
  for (redValue = 255, greenValue = 0; greenValue <= 255; redValue--, greenValue++) {
    setColor(redValue, greenValue, blueValue);
    delay(10);
  }
  // Fade from green to blue
  for (greenValue = 255, blueValue = 0; blueValue <= 255; greenValue--, blueValue++) {
    setColor(redValue, greenValue, blueValue);
    delay(10);
  }
  // Fade from blue to red
  for (blueValue = 255, redValue = 0; redValue <= 255; blueValue--, redValue++) {
    setColor(redValue, greenValue, blueValue);
    delay(10);
  }
}

// Function to set the color of the RGB LED
void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}