#include <EEPROM.h>

void initEEPROM(){
  for (int i = 0; i <= 2; i++) {
    EEPROM.get(i * 10, timerData[i]);
  }
  setAlarm();
}

void saveData(int address){
  printToLCD(1,0,"Saving Data to");
  printToLCD(0,1,"Memory Pls Wait");

  EEPROM.put(address * 10, timeData);
  timerData[address] = timeData;
  currentAlarmIndex = 0;
  rtc.clearAlarm(1);
  setAlarm();
  delay(2000);
}
