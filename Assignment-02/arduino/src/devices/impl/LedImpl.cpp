#include "devices/api/Led.h"
#include "Arduino.h"
Led::Led(int Pin)
{
    this->pin = Pin;
    pinMode(pin, OUTPUT);
}

void Led::switchOn()
{
    digitalWrite(pin, HIGH);
}

void Led::switchOff()
{
    digitalWrite(pin, LOW);
}
