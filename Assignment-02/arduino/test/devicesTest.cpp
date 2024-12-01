#include <Arduino.h>
#include "set-up.h"
#include "devices/api/Button.h"
#include "devices/api/LCD.h"
#include "devices/api/Led.h"
#include "devices/api/Pir.h"
#include "devices/api/SensorTemp.h"
#include "devices/api/ServoMotor.h"
#include "devices/api/Sonar.h" 

Button* openButton;
Button* closeButton;
Led* ledGreen;
Led* ledRed;
ServoMotor* servo;
Pir* pir;
SensorTemp* temp;
LCD* lcd;
LiquidCrystal_I2C pLcd = LiquidCrystal_I2C(0x27,20,4);

Sonar* dist;
void setup() {
  Serial.begin(9600);
openButton = new Button(BUTTON_OPEN);
closeButton = new Button(BUTTON_CLOSE);
ledGreen = new Led(GREEN_LED);
ledGreen->switchOff();
ledRed = new Led(RED_LED);
ledRed->switchOff();
servo = new ServoMotor(SERVO_MOTOR);
//servo->on();
servo->setPosition(0);
pir = new Pir(PIR_PIN);
//pir->calibrate();
temp = new SensorTemp(TEMP_);
lcd = new LCD();
lcd->setup();
  pLcd.init();
  pLcd.backlight();
dist = new Sonar(SONAR_ECHO, SONAR_TRIG);
dist->setTemperature(temp->getTemperature());
}

void loop() {
  /*
  openButton->sync();
  pir->sync();
  if(openButton->isPressed() && pir->isDetected()){
    servo->on();
    Serial.println("Button open Pressed");
    ledGreen->switchOn();
    ledRed->switchOff();
    servo->setPosition(90);
    servo->off();
  }
    closeButton->sync();
  if(closeButton->isPressed()){
    servo->on();
    Serial.println("Button close Pressed");
    ledGreen->switchOff();
    ledRed->switchOn();
    servo->setPosition(0);
    servo->off();
  }
  /*
    if(temp->getTemperature()>30){
    servo->on();
    Serial.print("Temperature: ");
    Serial.println(temp->getTemperature());
    ledGreen->switchOff();
    ledRed->switchOn();
    servo->setPosition(0);
    servo->off();
  }
  */
 
  lcd->turnOff();
  delay(2000);
  lcd->turnOn();
  delay(2000);
  lcd->displayAwake();
  delay(2000);
  lcd->displayClose();
  delay(2000);
  lcd->displayClosingContainer();
  delay(2000);
  lcd->displayEmptingContainer();
  delay(2000);
  lcd->displayFull();
  delay(2000);
  lcd->displayOpen();
  delay(2000);
  lcd->displayOpeningContainer();
  delay(2000);
  lcd->displayProblemDetected();
  delay(2000);
  lcd->displayRestore();
  delay(2000);

/*
pLcd.display();
pLcd.setCursor(0, 0);
pLcd.print(temp->getTemperature());
pLcd.clear();
Serial.println("alive");
delay(1000);*/
/*
dist->setTemperature(temp->getTemperature());
Serial.println(dist->getDistance());*/
}