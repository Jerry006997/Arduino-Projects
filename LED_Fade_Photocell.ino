int ledPin = 9; // sets pin 9 to the name ledPin
int sensePin = A0; // sets sensePin to pin A0 
int threshold = 500; // makes the photocell wait to 500 brightness until it does its thing
int fadeAmount = 1; // makes the led step by 1 when fading
int brightness = 0; // sets brightness to start at zero
unsigned long previousMillis = 0; // tells when the led took a step
unsigned long currentTime = 0; // stores the current time in milliseconds since the Arduino started
const long interval = 5; // how long to wait (in ms) between brightness updates

void setup() { // runs once
  pinMode(ledPin, OUTPUT); // sets the pin 9 as a output
}
void loop() { // runs forever
  int senseState = analogRead(sensePin); // reads the sense Pin from 0 to 1023 and sets the name as senseState
  currentTime = millis(); // sets currentTime to when the board powered up in milliseconds 

  if (senseState >= threshold) { // if the senseState is greaterthan or equal to the threshold do the next thing
    if (currentTime - previousMillis >= interval) { // if the currentTime - the previousMillis are greaterthan or equal to the interval then do the next things 
    previousMillis = currentTime; // set the previousMillis to the currentTime
    brightness += fadeAmount; // brightness = brightness + fadeAmount
      if (brightness <= 0 || brightness >= 255) { // if the brightness is less then or equal to 0 or if the brightness is greaterthan or equal to 255 do the next things
      fadeAmount = -fadeAmount; // fadeAmount = the - fadeAmount so basicly steps up then steps down
      }
      analogWrite(ledPin, brightness); // analogWrite pin 9 to the brightness
    }
 } else { // else
  analogWrite(ledPin, LOW); // analogWrite pin 9 to 0 
  brightness = 0; // then set brightness back to 0
 }
}

