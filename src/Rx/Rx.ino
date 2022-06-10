#include <M5Stack.h>
/*COM11*/
//defines pin numbers
int LEDPinNo = 22;
int reading = 0;
int new_reading = 0;

const int trigPin = 2;
const int echoPin = 5;

long duration;
float distance, Pdistance;
int sync = 0;

void setup() {
  // Initialize the M5Stack object
  M5.begin();
  
  //M5.Lcd.printf("This is the receiver \r\n");

  pinMode(LEDPinNo, INPUT); //22pin INPUT mode

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  M5.Lcd.setTextSize(4);
}

void loop() {
  
  if(sync==0){
    new_reading = digitalRead(LEDPinNo);
    if(new_reading==1){
      //M5.Lcd.printf("Sync completed \r\n");
      //reading = new_reading;
      sync = 1;
    }

  }

  if(sync==1){
    Calc();
    distance = (duration*0.034)/2;
    M5.Lcd.setCursor(4,0);
    M5.Lcd.print(distance);
    M5.Lcd.print(" cm");
  }

  M5.update();

}

void Calc(){
    duration=0;
    Trigger_US();
    while(digitalRead(echoPin)==HIGH);
    delay(32);
    Trigger_US();
    duration = pulseIn(echoPin, HIGH);
  }

void Trigger_US(){
    // Fake trigger the US sensor
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  }
