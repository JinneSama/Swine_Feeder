#include "RTC.h"
#include "LCD.h"
#include "Memory.h"
#include "GUIs.h"
#include "Buttons.h"
#include "MotorControl.h"
#include "LoadCell.h"

void setup() { 
 initRTC();
 initLCD();
 initButtons();
 initEEPROM();
 initMotor();
}

void loop() { 
 buttonLoop();
}
