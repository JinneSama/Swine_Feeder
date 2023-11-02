unsigned long mainScreenInterval = 5000;
unsigned long mainScreenTime = 0;

int screen = 0;

void modeSelect(int _mode, bool cls, int selector,bool selectorCls);
void setTimer(int _mode, int selector,bool selectorCls);

int _hour = 0;
int _minute = 0;
char _amp = 'A';
float _weight = 0.00;


char details[50];

void Screen01(){
  printToLCD(0 , 0 , "Auto SwineFeeder");
  printToLCD(2 , 1,getTimeRTC());
}

void Screen02(){
  printToLCD(3 , 0 , "Feeding #1");
  sprintf(details, "%02d:%02d %cM  ", timerData[0]._hour,timerData[0]._minute,timerData[0]._amp);
  printToLCD(4 , 1,details);
}

void Screen03(){
  printToLCD(3 , 0 , "Feeding #2");
  sprintf(details, "%02d:%02d %cM  ", timerData[1]._hour,timerData[1]._minute,timerData[1]._amp);
  printToLCD(4 , 1,details);
}

void Screen04(){
  printToLCD(3 , 0 , "Feeding #3");
  sprintf(details, "%02d:%02d %cM  ", timerData[2]._hour,timerData[2]._minute,timerData[2]._amp);
  printToLCD(4 , 1,details);
}

void loopMainScreens(){
  if(screen == 0){
    Screen01();
  }else if(screen == 1){
    Screen02();
  }else if(screen == 2){
    Screen03();
  }else if(screen == 3){
    Screen04();
  }
    
  if(millis() - mainScreenTime > mainScreenInterval){
    if(screen >= 3){
      screen = 0;
    }else{
      screen++;
    }
    mainScreenTime = millis();
    clearScreen();
  }
}

void modeSelect(int _mode , bool cls , int selector,bool selectorCls){
  if (cls){
    _hour = timerData[_mode - 1]._hour;
    _minute = timerData[_mode - 1]._minute;
    _amp = timerData[_mode - 1]._amp;
    _weight = timerData[_mode - 1]._weight;
    clearScreen();
  }
  if(_mode == 0){
    loopMainScreens();
  }else{
    
    setTimer(_mode,selector,selectorCls);
  }
}

void addToDetails(int selector , int toAdd){
  if(selector == 1){
    if(_hour >= 12){
      _hour = 0;
    }else{
      _hour += toAdd; 
      if(_hour <= 0){
        _hour = 0;
      }
    }
  }else if(selector == 2){
    if(_minute >= 60){
      _minute = 0;
    }else{
      _minute += toAdd; 
      if(_minute <= 0){
        _minute = 0;
      }
    } 
  }else if(selector == 3){
    if(toAdd == 1){
      _amp = 'A';
    }else{
      _amp = 'P';
    }
  }else if(selector == 4){
    if(toAdd == -1){
      _weight -= 0.10;
      if (_weight < 0){
        _weight = 0.00;
      }
    }else{
      _weight += 0.10;
    }
  }
}

void setTimer(int _mode, int selector, bool selectorCls){
  if(selector < 5){    
    sprintf(details, "%02d:%02d %cM  ", _hour,_minute,_amp);
    printToLCD(0 , 1 , details + String(_weight) + "kg");
  }
  if (selectorCls){
    printToLCD(0,0, "                ");
  }
  if(selector == 0){
    printToLCD(1 , 0 , "Set Feeding #" + String(_mode));
  }else if(selector == 1){
    writeChar(0,0,0,2);
  }else if(selector == 2){
    writeChar(3,0,0,2);
  }else if(selector == 3){
    writeChar(6,0,0,2);
  }else if(selector == 4){
    writeChar(10,0,0,4);
  }else if(selector == 5){
    if(selectorCls){
      clearScreen();
    }
    printToLCD(1,0, "Press Mode to");
    printToLCD(1,1, "Save Settings");
    
    timeData._hour = _hour;
    timeData._minute = _minute;
    timeData._amp = _amp;
    timeData._weight = _weight;
  }
}
