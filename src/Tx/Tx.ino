#include <M5Stack.h>
/*COM4*/
//define pins for physical syncing
int LEDPinNo = 22;
int reading = 0;
int sync = 0;
// defines pins numbers
const int trigPin = 2;
const int echoPin = 5;
// defines variables
long duration;
int distance;

void setup() {
  // Initialize the M5Stack object
  M5.begin();
  
  M5.Lcd.printf("This is the transmitter \r\n");
  //Pin for syncing
  pinMode(LEDPinNo, OUTPUT); //22pin OUTPUT mode
  digitalWrite(LEDPinNo, LOW);

  //Pins for transmitting
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  M5.Lcd.setTextSize(4);
}

void loop() {
  if(M5.BtnA.wasPressed()) {
    M5.Lcd.printf("Time Syncing \r\n");
    //M5.Lcd.printf("LED ON \r\n");
    digitalWrite(LEDPinNo, HIGH);
    //reading = digitalRead(LEDPinNo);
    //M5.Lcd.printf("Pin value: %d\r\n",reading);
    sync = 1;
    M5.Lcd.printf("Time Syncing \r\n");
  }

  if(sync==1){
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    delay(32);
  }

  if(M5.BtnB.wasPressed())
  {
    M5.Lcd.printf("Sync reset \r\n");
    //M5.Lcd.printf("LED OFF \r\n");
    digitalWrite(LEDPinNo, LOW);
    //reading = digitalRead(LEDPinNo);
    //M5.Lcd.printf("Pin value: %d\r\n",reading);
  }

  M5.update();
  
}
