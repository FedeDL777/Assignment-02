#include "api/Button.h"
#include "Arduino.h"


Button::Button(int pin)
{
    this->pin=pin;
    pinMode(pin, OUTPUT);
    sync();
}

bool Button::pressed()
{
    return pressed;
}
/*
bool Button::clicked()
{
    return false;
}*/

void Button::sync()
{
    digitalRead(pin) == HIGH ? pressed = true : pressed = false;
    updateSyncTime(millis());
}
void Button::updateSyncTime(long time)
{
    lastTimeSync = time;
}

long Button::getLastSyncTime()
{
    return lastTimeSync;
}
