//Ultrasonic Pin to Arduino Pin
//connect Vcc to 5V on Arduino
//connect Gnd to Gdn on Arduino
//connect trig to pin 8
//connect echo to pin 9
const int trigPin=8;
const int echoPin=9;
long duration;
int distance;
void setup() {
  // put your setup code here, to run once:
pinMode(trigPin, OUTPUT); //Sets the trigPin as an Output
pinMode(echoPin, INPUT); //Sets the echoPin as an Input
Serial.begin(9600);
}

void loop() {
//Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
//Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
//Reads the echoPin, returns the sound wave travel time in microseconds
duration=pulseIn(echoPin, HIGH);
//Calculating the distance
distance=duration*0.034/2;
//Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance); //Reads distance in cm
}
