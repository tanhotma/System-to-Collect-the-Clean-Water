//================  Arduino Pin Setup ================//


//Valve Pins
const int cleanWaterValvePin = 2; //Pin controlling the clean water valve.
const int dirtyWaterValvePin = 3; //Pin controlling the dirty water valve.

bool cleanWaterValveState = false; //Normally closed. Make these 
bool dirtyWaterValveState = false; //Normally closed. 


//Ultra-sonic sensor  pins + variables
const int sonicTrigPin=9;
const int sonicEchoPin=10;
double mySonicDistance = 0.0;
double myContainerRadius = 7;  // radius
long sonicDuration;

void setup() {
Serial.begin(9600); // start serial debug
  
//================= Iniatilize Arduino IO ===========//

//Valve
pinMode(cleanWaterValvePin, OUTPUT);
pinMode(dirtyWaterValvePin, OUTPUT);

//UltraSonic Sensor
pinMode(sonicTrigPin, OUTPUT); //Sets the trigPin as an Output
pinMode(sonicEchoPin, INPUT);  //Sets the echoPin as an Input


}

void loop() {
sonicGetDistance();
Serial.print("Gallons: ");
Serial.println(getWaterGallon()); // print current volume
Serial.print("Volume: ");
Serial.println(getWaterVolume()); // print current volume

delay(500);
}


double getWaterVolume() //cm^3
{
  // A = pi * r^2
  //V = A * H
  // H = sonic distance
 double pi = 3.14;

  return mySonicDistance * pi * myContainerRadius * myContainerRadius;
}
double getWaterGallon(){
  return getWaterVolume()/3,785.41;     //3,785.41 cm^3 / gal to get gallons
}
void sonicGetDistance(){

//Clears the trigPin
digitalWrite(sonicTrigPin, LOW);
delayMicroseconds(2);
//Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(sonicTrigPin, HIGH);
delayMicroseconds(10);
digitalWrite(sonicTrigPin, LOW);
//Reads the echoPin, returns the sound wave travel time in microseconds
sonicDuration=pulseIn(sonicEchoPin, HIGH);
//Calculating the distance
mySonicDistance=sonicDuration*0.034/2;
//Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(mySonicDistance); //Reads distance in cm

}

void cleanValveState(bool myState){ // 1 == OPEN || 0 == closed
  cleanWaterValveState = myState;
  digitalWrite(cleanWaterValvePin, cleanWaterValveState);
}

void dirtyValveState(bool myState){ // 1 == OPEN || 0 == closed
  dirtyWaterValveState = myState;
  digitalWrite(dirtyWaterValvePin, dirtyWaterValveState);
}


