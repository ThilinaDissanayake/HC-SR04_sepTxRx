#include <M5Stack.h>
#include <stdlib.h>

/*COM11*/
//defines pin numbers
int LEDPinNo = 22;
int reading = 0;
int new_reading = 0;

const int trigPin = 2;
const int echoPin = 5;

int duration = 16000;
float distance, Pdistance;
int sync = 0;

unsigned long now = 0;
int num = 0;

TaskHandle_t task_handl1;
TaskHandle_t task_handl2;

void distDisplay(void *pvParameters){
  while(true){
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.print(distance);
    M5.Lcd.print(" cm");
    delay(200);
    //Serial.println(digitalRead(echoPin));
    
  }
  vTaskDelete(NULL);
}


void setup() {
  // Initialize the M5Stack object
  M5.begin();
  
  //M5.Lcd.printf("This is the receiver \r\n");

  pinMode(LEDPinNo, INPUT); //22pin INPUT mode

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  M5.Lcd.setTextSize(4);
  //task to display distance on the LCD display
  xTaskCreatePinnedToCore(&distDisplay, "distDisplay", 10000, NULL, 1, &task_handl1, 0);
}

void loop() {
  if(sync==0){
    now = micros();
    new_reading = digitalRead(LEDPinNo);
    if(new_reading==1){
      delayMicroseconds(40943);//wait until the transmitter process display content
      sync = 1;
    }

  }

  if(sync==1){
    //now = micros();
    //Serial.println(micros()-now);
    
    Calc();
    distance = (duration*0.034);//(duration*0.00294117647)/4;//(duration*0.034)/2;
    //Serial.println(micros()-now);
    //Serial.println(duration);
  }

  if(M5.BtnB.wasPressed())
  {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.printf("Sync reset \r\n");
    digitalWrite(LEDPinNo, LOW);
  }

  M5.update();
  
  
}

void pulseIn_func(){
  while(digitalRead(echoPin)==LOW);
  int start_time = micros();
  while(digitalRead(echoPin)==HIGH);
  duration = micros() - start_time;
  
}

void Calc(){
    //now = micros();
    Trigger_US();
    //while(digitalRead(echoPin)==HIGH);
    //if(digitalRead(echoPin)==LOW){
      //pulseIn_func();
      //duration = 16000;
      duration = pulseIn(echoPin, HIGH);//Try adding a timeout
      //Serial.println(micros()-now);
      //Serial.println(duration);
      //delayMicroseconds(2000);
      //if(duration<=16000){
      delayMicroseconds(40000-duration);//delayMicroseconds(40000 - (duration));
        
      //}
    //}
    //else if(digitalRead(echoPin)==HIGH){
    //  while(digitalRead(echoPin)==HIGH);
    //}
       
    
    //if(digitalRead(echoPin)==HIGH){
    //  while(digitalRead(echoPin)==HIGH);
    //}
   //Serial.println(micros()-now);

    
  }

void Trigger_US(){
    // Fake trigger the US sensor
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  }
