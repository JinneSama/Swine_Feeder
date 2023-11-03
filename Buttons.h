const int selectBtn = 6;
const int modeBtn = 3;
const int upBtn = 4;
const int downBtn = 5;

int selectState = 1;
int modeState = 1;
int upState = 1;
int downState = 1;

int lastSelectState = 1;
int lastModeState = 1;
int lastUpState = 1;
int lastDownState = 1;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

int modes = 0;
int selector = 0;

bool debounce(void);

void initButtons() {
  pinMode(selectBtn, INPUT_PULLUP);
  pinMode(modeBtn, INPUT_PULLUP);
  pinMode(upBtn, INPUT_PULLUP);
  pinMode(downBtn, INPUT_PULLUP);
}

void buttonLoop() {
  selectState = !digitalRead(selectBtn);
  modeState = !digitalRead(modeBtn);
  upState = !digitalRead(upBtn);
  downState = !digitalRead(downBtn);
  
  if(selectState && lastSelectState && modes > 0){
    if(debounce()){
      if(selector <= 4){
        selector += 1;
      }else{
        selector = 0;
      }
    }
  }

  if(modeState && lastModeState){
    if(debounce()){
      if(selector == 5){
        saveData(modes - 1);
        modes -= 1;
      }
      selector = 0;
      if(modes <= 2){
        modes += 1;
      }else{
        modes = 0;
      }
    }
  }

  if(upState && lastUpState && modes > 0){
    if(debounce()){
      addToDetails(selector,1);
    }
  }

  if(downState && lastDownState){
    if(debounce()){
      addToDetails(selector,-1);
    }
  }

  modeSelect(modes,modeState,selector,selectState);
  lastSelectState = !selectState;
  lastModeState =!modeState;
  lastUpState = !upState;
  lastDownState = !downState;
  
  //printToLCD(10,1, String(selectState) + String(modeState) + String(upState) + String(downState));
}

bool debounce(){
  if (millis() - lastDebounceTime > debounceDelay) {
    lastDebounceTime = millis();  
    return true;
  }
}
