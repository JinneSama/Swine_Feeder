#include <EEPROM.h>

TimeData timerData[3];

void initEEPROM(){
  for (int i = 0; i <= 2; i++) {
    EEPROM.get(i * 10, timerData[i]);
  }
}

void saveData(int address){
  printToLCD(1,0,"Saving Data to");
  printToLCD(0,1,"Memory Pls Wait");

  EEPROM.put(address * 10, timeData);
  timerData[address] = timeData;
  delay(2000);
}
