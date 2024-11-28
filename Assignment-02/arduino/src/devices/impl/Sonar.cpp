#include "devices/api/Sonar.h"
#include "Arduino.h"

Sonar::Sonar(int echoPin, int trigPin, float temperature)
{
    this->echoPin = echoPin;
    this->trigPin = trigPin;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    temperature=20;
}

float Sonar::getSoundSpeed(){
    soundSpeed = 331.5 + 0.6*temperature; 
}
float Sonar::getDistance()
{
    soundSpeed = getSoundSpeed();
    /* invio impulso */
    digitalWrite(trigPin,LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin,LOW);
    
    long tUS = pulseInLong(echoPin, HIGH);

    double t = tUS / 1000.0 / 1000.0 / 2;
    double d = t*soundSpeed;
    return d;
}

void Sonar::setTemperature(float temp){
    temperature=temp;
}