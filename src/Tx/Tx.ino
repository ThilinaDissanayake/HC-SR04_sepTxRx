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

unsigned long now = 0;

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
  //unsigned long now = millis();
  if(M5.BtnA.wasPressed()) {
    now = micros();
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0,0);
    M5.Lcd.printf("Time Syncing \r\n");
    //M5.Lcd.printf("LED ON \r\n");
    digitalWrite(LEDPinNo, HIGH);
    //reading = digitalRead(LEDPinNo);
    //M5.Lcd.printf("Pin value: %d\r\n",reading);
    sync = 1;
    //M5.Lcd.printf("Time Syncing \r\n");
  }

  if(sync==1){
    //now = micros();
    //Serial.println(micros()-now);
    //exit(0);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(42228);
    //Serial.println(micros()-now);
  }

  if(M5.BtnB.wasPressed())
  {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.printf("Sync reset \r\n");
    digitalWrite(LEDPinNo, LOW);
  }

  M5.update();
  
  
}
