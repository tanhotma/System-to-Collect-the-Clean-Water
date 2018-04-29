#include "SD.h"
#include "SPI.h"
#include <string.h>
//================  Arduino Pin Setup ================//

//Valve Pins
const int cleanWaterValvePin = 2; //Pin controlling the clean water valve.
const int dirtyWaterValvePin = 3; //Pin controlling the dirty water valve.

bool cleanWaterValveState = false; //Normally closed. Make these 
bool dirtyWaterValveState = false; //Normally closed. 

//Ultra-sonic sensor  pins + variables
double pi = 3.14;

const int sonicTrigPin=8; // ultrasonic sensor
const int sonicEchoPin=9; //
double mySonicDistance = 0.0;
long sonicDuration;

double myContainerRadius = 7;  // radius. cm.
double myContainerHeight = 30; //cm
double myContainerVolume =  myContainerHeight*pi*myContainerRadius*myContainerRadius; // cm^3

//SD Card variables
const int CSpin = 11;
String dataString = ""; // holds the data to be written to the SD card
File sensorData; // create file object

void setup() {
Serial.begin(9600); // start serial debug
  
//================= Iniatilize Arduino IO ===========//

//Valve
pinMode(cleanWaterValvePin, OUTPUT);
pinMode(dirtyWaterValvePin, OUTPUT);

//UltraSonic Sensor
pinMode(sonicTrigPin, OUTPUT); //Sets the trigPin as an Output
pinMode(sonicEchoPin, INPUT);  //Sets the echoPin as an Input

//================= Iniatilize SD Card ===========//
Serial.print("Initializing SD card...");
pinMode(CSpin, OUTPUT);
//
// see if the card is present and can be initialized:
if (!SD.begin(CSpin)) {
Serial.println("Card failed, or not present");
// don't do anything more:
return;
}
Serial.println("card initialized.");
}

void loop() {
  
sonicGetDistance();

Serial.print("Gallons: ");
Serial.print(getWaterGallons()); // print current volume
Serial.println(" gals");

Serial.print("Volume: ");
Serial.print(getWaterVolume()); // print current volume
Serial.println(" cm^3");

delay(500);
dataString = "My gallons: " + String(getWaterGallons()); //updates every time ran.

}

void writeString(){
saveData(); // save to SD card
delay(60000); // delay before next write to SD Card, adjust as required
}

double getAirVolume() //cm^3
{
  // A = pi * r^2
  //V(water) = V(container)-Volume(air) = Vc - Va(A * H)
  // H = sonic distance

  return mySonicDistance * pi * myContainerRadius * myContainerRadius;
}

double getWaterVolume(){
  return myContainerVolume - getAirVolume();
}

double getWaterGallons(){
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

void saveData(){
if(SD.exists("data.csv")){ // check the card is still there
// now append new data file
sensorData = SD.open("data.csv", FILE_WRITE);
if (sensorData){
sensorData.println(dataString);
sensorData.close(); // close the file
}
}
else{
Serial.println("Error writing to file !");
}
}


