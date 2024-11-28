#include "Arduino.h"
#include "api/Pir.h"

Pir::Pir(int pin){
    this->pin=pin;
    pinMode(pin, INPUT);
}

bool Pir::isDetected()
{
    return present;
}

void Pir::calibrate()
{
    delay(10000);
}

void Pir::sync()
{
    digitalRead(pin) == HIGH ? present = true : present = false;
    lastTimeSync = millis();

}

long Pir::getLastSyncTime()
{
    return lastTimeSync;
}
