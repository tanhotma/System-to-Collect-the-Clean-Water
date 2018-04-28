//================  Arduino Pin Setup ================//

const int cleanWaterValvePin = 2; //Pin controlling the clean water valve.
const int dirtyWaterValvePin = 3; //Pin controlling the dirty water valve.

bool cleanWaterValveState = false; //Normally closed. Make these 
bool dirtyWaterValveState = false; //Normally closed. 

void setup() {
  
//================= Iniatilize Arduino IO ===========//
pinMode(cleanWaterValvePin, OUTPUT);
pinMode(dirtyWaterValvePin, OUTPUT);


}

void loop() {

  cleanValveState(true);
  delay(500);
  cleanValveState(false);
  delay(500);
  dirtyValveState(true);
  delay(500);
  dirtyValveState(false);
  delay(500);

}

void cleanValveState(bool myState){ // 1 == OPEN || 0 == closed
  cleanWaterValveState = myState;
  digitalWrite(cleanWaterValvePin, cleanWaterValveState);
}

void dirtyValveState(bool myState){ // 1 == OPEN || 0 == closed
  dirtyWaterValveState = myState;
  digitalWrite(dirtyWaterValvePin, dirtyWaterValveState);
}


