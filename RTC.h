#include "RTClib.h"
#include <Wire.h>
#include <Arduino.h>

#define INT_PIN 2

RTC_DS3231  rtc;

struct TimeData {
  int _hour;
  int _minute;
  char _amp;
  float _weight;
};

TimeData timeData;
TimeData timerData[3];

int currentAlarmIndex = 0;

int compareIndices(const void *a, const void *b);
void sortData(int index);

void handleAlarm() {
  currentAlarmIndex = (currentAlarmIndex + 1) % 3;
}
void setAlarm(){
  sortData(currentAlarmIndex);
}

void initRTC() {
  rtc.begin();
  pinMode(INT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INT_PIN), handleAlarm, FALLING);
  if(rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  rtc.disable32K();
  
  rtc.clearAlarm(1);
  rtc.clearAlarm(2);

  rtc.writeSqwPinMode(DS3231_OFF);
  rtc.disableAlarm(2);
  setAlarm();
}

String getTimeRTC(){
  DateTime _time = rtc.now();
  char amp = 'A';
  char _timeNow[40];
  int _hour = 0;
  if (_time.hour() > 12){
    amp = 'P';
    _hour = _time.hour() - 12;
  }else{
    amp = 'A';
    _hour = _time.hour();
  }
  sprintf(_timeNow,"%02d:%02d:%02d %cM",_hour,_time.minute(),_time.second(),amp);
  return _timeNow;
}

void sortData(int index){
  int _hour = timerData[index]._hour;
  rtc.setAlarm1(DateTime(2023,11,3,_hour,timerData[index]._minute , 0) , DS3231_A1_Hour);
  
}

void RTCloop(){
  if (rtc.alarmFired(1)) {
    rtc.clearAlarm(1);
    clearScreen();
    printToLCD(3 , 0 , "Feeding Now");
    //startProcess();
    delay(2000);
  }
}
