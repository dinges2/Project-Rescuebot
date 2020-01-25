#include <arduinio.h>
#include <Wire.h>

#define irLeft 2
#define irRight 3
#define motorRightForward 5
#define motorRightBackward 6
#define motorLeftForward 7
#define motorLeftBackward 8
#define trigUltrasonic1 9
#define echoUltrasonic1 10
#define trigUltrasonic2 11
#define echoUltrasonic2 12





// defines variables
long duration;
long ultraSonic1;
long ultraSonic2;
int distance;
int driveMode = 0;
int manual = 6;


void setup(){
    Serial.begin(9600);
    Wire.begin(1);
    Wire.onReceive(receiveEvent);
    
    //set pins as input ir sensor
    pinMode(irLeft, INPUT);
    pinMode(irRight, INPUT);
    
    //Set pins as outputs motor
    pinMode(motorRightForward, OUTPUT);
    pinMode(motorRightBackward, OUTPUT);
    pinMode(motorLeftForward, OUTPUT);
    pinMode(motorLeftBackward, OUTPUT);
    
    //set pins ultrasone sensor
    pinMode(trigUltrasonic1, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoUltrasonic1, INPUT); // Sets the echoPin as an Input
    pinMode(trigUltrasonic2, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoUltrasonic2, INPUT);
    
  
  
}
void forward(){
  //this code will turn the motors clockwise
    digitalWrite(motorRightForward, HIGH);
    digitalWrite(motorRightBackward, LOW);
    digitalWrite(motorLeftForward, HIGH);
    digitalWrite(motorLeftBackward, LOW);
}

void backward(){
  //this code will turn the motors counterclockwise
    digitalWrite(motorRightForward, LOW);
    digitalWrite(motorRightBackward, HIGH);
    digitalWrite(motorLeftForward, LOW);
    digitalWrite(motorLeftBackward, HIGH);
}

void right(){
  //This code will turn the robot to the right
    digitalWrite(motorRightForward, LOW);
    digitalWrite(motorRightBackward, HIGH);
    digitalWrite(motorLeftForward, HIGH);
    digitalWrite(motorLeftBackward, LOW);
}

void left(){
  //This code will turn the robot to the left
    digitalWrite(motorRightForward, HIGH);
    digitalWrite(motorRightBackward, LOW);
    digitalWrite(motorLeftForward, LOW);
    digitalWrite(motorLeftBackward, HIGH);
}

void park(){
  //This code will stop the robot 
    digitalWrite(motorRightForward, LOW);
    digitalWrite(motorRightBackward, LOW);
    digitalWrite(motorLeftForward, LOW);
    digitalWrite(motorLeftBackward, LOW);
}

void receiveEvent(){
  int temp = 0;
  temp = Wire.read();
  
  if(temp <= 4){
    driveMode = temp;
    //Serial.println(driveMode);
  }
  else{
    manual = temp;
    //Serial.println(manual);
  }
}

void sonarSensor(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
}




void loop(){
  
  sonarSensor(trigUltrasonic1, echoUltrasonic1);
  ultraSonic1 = distance;
  sonarSensor(trigUltrasonic2, echoUltrasonic2);
  ultraSonic2 = distance;
  //Serial.print("ultrasonic1: ");
  //Serial.println(ultraSonic1);
  //Serial.print("ultrasonic2: ");
  //Serial.println(ultraSonic2);
  
  
  if(manual == 5){
    Serial.println("automatic");

    if(digitalRead(irLeft) && digitalRead(irRight)){
      backward();
      delay(500);
      right();
      delay(1000);
    }
    
    else if(ultraSonic1 < 20) {
      right();
      //Serial.print("ultrasonic1: ");
      //Serial.println(ultraSonic1);
      
    }

    else if(ultraSonic2 > 20){
      backward();
      delay(2000);
      right();
      delay(2000);
      //Serial.print("ultrasonic2: ");
      //Serial.println(ultraSonic2);
    }
    
    
    else if(digitalRead(irLeft)){
      right();
    }

    else if(digitalRead(irRight)){
      left();
    }
    
    else{
      forward();
    }

    
    
  }

  else if(manual == 6){
    //Serial.println("manual");

    if(driveMode == 0){
      park();
      //Serial.println("parking");
    }
    else if(driveMode == 1){
      forward();
      //Serial.println("forward");
    }

    else if(driveMode == 2){
      backward();
      //Serial.println("backward");
    }

    else if(driveMode == 3){
      left();
      //Serial.println("left");
    }

    else if(driveMode == 4){
      right();
      //Serial.println("right");
    }
  }

    

  

  
  

}
