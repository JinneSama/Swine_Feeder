#include "BTS7960.h"

const uint8_t EN = 8;
const uint8_t L_PWM = 9;
const uint8_t R_PWM = 10;
#define potPin A0

BTS7960 servo(EN, L_PWM, R_PWM);

void initMotor(){
  pinMode(potPin , INPUT);
}

void moveMotor(int angle) {
  
  int angleValue = map(angle, 0 ,360 , 0 , 1025);
  int potValue = analogRead(potPin);
 
  int angleDiff = abs(angleValue - potValue);
  int motorSpeed = map(angleDiff, 0, 1025, 0, 1700);
  if (motorSpeed > 255) {
    motorSpeed = 255;
  } 
  if (motorSpeed < 30) {
    motorSpeed = 0;
  }
  servo.Enable();
  
  if(potValue < angleValue){
    servo.TurnLeft(motorSpeed); 
  }
  if (potValue > angleValue){
    servo.TurnRight(motorSpeed);
  }
  if (potValue == angleValue){
    servo.Stop();
  }
}
