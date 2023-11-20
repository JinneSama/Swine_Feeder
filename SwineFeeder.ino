#include "LCD.h"
#include "RTC.h"
#include "Memory.h"
#include "GUIs.h"
#include "Buttons.h"
#include "MotorControl.h"
#include "LoadCell.h"
#include "Process.h"

void setup() { 
 initRTC();
 initEEPROM();
 initLCD();
 initButtons();
 initMotor();
}

void loop() { 
 buttonLoop();
 RTCloop();
}
