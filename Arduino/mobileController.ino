/*
 * 2 Wheel Mobile Robot 
 * 2017
 * IEEE University of Ioannina
 * ieeesbuoi (at) gmail.com
 */
 
#include <AFMotor.h>
#include <Servo.h>

#define echoPin 24 // Echo Pin
#define trigPin 26 // Trigger Pin
#define LEDPin 13 // Onboard LED
#define objAvoidPin 22
#define leftEncPin 40
#define rightEncPin 43

AF_DCMotor leftMotor(4);  // M4 - LEFT motor
AF_DCMotor rightMotor(2);  // M2 - RIGHT motor

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance
int leftMotorSpeed = 5;
int rightMotorSpeed = 5;

int leftEncoderClicks = 0;
int rightEncoderClicks = 0;

Servo servo;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Mobile robot up and ready...");
  pinMode(objAvoidPin, INPUT);
  
  //pinMode(trigPin, OUTPUT);
  //pinMode(echoPin, INPUT);
  //pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)
  pinMode(leftEncPin, INPUT);
  pinMode(rightEncPin, INPUT);
  servo.attach(28);
  
  // Turn motors on
  leftMotor.setSpeed(200);
  rightMotor.setSpeed(200);
 
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  delay(3000);
}

void checkUltrasonicDistance() {
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration/58.2;
  Serial.println(distance);
  if ( (distance >= 0) && (distance <= 25)) {  // Object detected
    
    //posStop();
  }
}

void moveForward(){
  Serial.print("Moving forward...");
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
  
  leftMotor.setSpeed(leftMotorSpeed);
  rightMotor.setSpeed(rightMotorSpeed);
}

void posStop(){
  Serial.println("Stoping the vehicle...");
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
}

void moveLeft(){
  Serial.print("moving left");
  leftMotor.setSpeed(0);
  rightMotor.setSpeed(150);
  delay(1200); 
  rightMotor.setSpeed(0);
}

void moveRight(){
  Serial.print("moving right");
  leftMotor.setSpeed(leftMotorSpeed);
  rightMotor.setSpeed(0);
  delay(1200);
  leftMotor.setSpeed(0);
}

void checkIRDistance() {
  int  value = digitalRead(objAvoidPin);
  if(value == 0) {  // Object detected
    posStop();
  }
}

void readEncoders() {
  int leftEncValue = digitalRead(leftEncPin);
  int rightEncValue = digitalRead(rightEncPin);
  
  if (leftEncValue == 1) {
    leftEncoderClicks +=1;
  }
  if (rightEncValue == 1) {
    rightEncoderClicks +=1;
  }
}

void calculateEncTime() {
  if( leftEncoderClicks == 0) {
    //start_time
  }
  if( leftEncoderClicks == 2) {
    //end_time
  }
}

// Turns the servo 180 degrees and finds the position that the mobile can go forward
void findEmptyRoute() {
  
  for(int i=10; i<160; i++) {
    Serial.println("Increasing servo ");
    servo.write(i);
      if(distance <=25) {
        checkUltrasonicDistance();
        Serial.print("Distance: ");
        Serial.println(distance);
      }
    
  }
}

void loop() {

  findEmptyRoute();
  //readEncoders();
  //calculateEncTime();
  
  //moveForward();
  //checkIRDistance();
  //checkUltrasonicDistance();

  //leftMotor.run(RELEASE);
  //delay(1000);
}
