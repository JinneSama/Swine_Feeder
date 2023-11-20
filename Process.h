#define OPEN_FEEDER 90
#define CLOSE_FEEDER 0

void startProcess(void);

void startProcess(){
  float weight = getWeight();
  while(weight <= timerData[currentAlarmIndex]._weight){
    moveMotor(OPEN_FEEDER);
  }
  moveMotor(CLOSE_FEEDER);
}
