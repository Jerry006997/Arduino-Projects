// Made by Jeriah Koenig 
const int ledPin = 13; // sets pin thirteen to the LED
const int buzzerPin = 12; // sets pin twelve to the buzzer
const int sensorPin = A0; // sets the sensors signal pin to pin A0 on the Arduino 
int sensorValue = 0; // Variable to store sensor reading 

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT); // sets pin thirteen as a output
  pinMode(buzzerPin, OUTPUT); // sets pin twelve as a output
  Serial.begin(9600); // start serial monitor at 9600 baud
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(sensorPin); // read sensor (0 - 1023)
  Serial.println(sensorValue); // print the value to serial monitor 
  
  if (sensorValue > 300 ) { // if sensor detects water (value above 100)
    digitalWrite(ledPin, HIGH); // turn led on
    digitalWrite(buzzerPin, HIGH); // turn buzzer on
  } else { // otherwise 
    digitalWrite(ledPin, LOW); // turn led off
    digitalWrite(buzzerPin, LOW); // turn buzzer off
  } 
    delay(100); // small pause before reading again
  
}
