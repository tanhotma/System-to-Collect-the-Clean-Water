// The purpose of this test is to turn on and off the motor
// using a relay
// by TAN HO
const int RELAY_PIN= 2;
 void setup () {
  pinMode( RELAY_PIN, OUTPUT);
   Serial.begin (9600);
 }
 void loop() {
  Serial.println("Relay ON"); // to know if motor is  on
 digitalWrite(RELAY_PIN, LOW); // turn on when we set the pin to LOW 
 delay(5000);

Serial.println( "Relay OFF");
 digitalWrite (RELAY_PIN, HIGH);
delay (1000); 
 }
