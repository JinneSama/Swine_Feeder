#include "RTClib.h"

RTC_DS1307  rtc;

struct TimeData {
  int _hour;
  int _minute;
  char _amp;
  float _weight;
};

TimeData timeData;

void initRTC() {
  rtc.begin();
  //rtc.setTime(19, 15, 0); 
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
