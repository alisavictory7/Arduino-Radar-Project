// Include the servo library
#include <Servo.h>. 

// Define Trig and Echo pin of the Ultrasonic sensor
const int trigPin = 10;
const int echoPin = 11;

// Create variables for the duration and the distance
long duration;
int distance;

// Create a servo object for controlling the servo motor
Servo myServo;


void setup() {
  pinMode(trigPin, OUTPUT);   // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);    // Sets the echoPin as an INPUT
  Serial.begin(9600);
  myServo.attach(12);         // Define on which pin the servo motor is attached
}

void loop() {
  // Rotate the servo motor from 15 to 165 degrees - can only 180 degrees at max
  for(int i=15;i<=165;i++){
    myServo.write(i);   // scan position of the servo
    delay(30);
    distance = calculateDistance();   // call a function for calculating the distance measured by the Ultrasonic Sensor for each degree
    
    Serial.print(i);          // Sends the current degree into the Serial Port
    Serial.print(",");        // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
    Serial.print(distance);   // Sends the distance value into the Serial Port
    Serial.print(".");        // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  }

  // Repeat the previous lines, but instead for 165 to 15 degrees.
  for(int i=165;i>15;i--){  
    myServo.write(i);
    delay(30);
    distance = calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
}

// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 microseconds - generate ultrasound
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);    // reads echoPin, returns the sound wave travel time in microseconds
  distance = duration*0.034/2;
  // In order to get the distance,
  // Multiply the received travel time value from echo pin by 0.034 cm/microseconds (speed of sound) 
  // Then divide by 2 - because the sound wave goes to object in front of it will have to go back to the sensor 
  
  return distance;
}


