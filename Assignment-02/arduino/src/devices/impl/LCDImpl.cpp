#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "set-up.h"
#include  "devices/api/LCD.h"


LCD::LCD()
{
    pLcd = new LiquidCrystal_I2C(0x27,20,4);
}
void LCD::setup()
{
    pLcd->clear();
    pLcd->init();

  pLcd->backlight();
  pLcd->noDisplay();
}



void LCD::turnOn()
{
    pLcd->backlight();
    pLcd->display();
  pLcd->clear();
}
void LCD::displayWelcome()
{
    this->turnOn();
    this->initCursor();
    pLcd->print("WELCOME TO");
    pLcd->setCursor(1,2);
    pLcd->print("SMART WASTE");
    pLcd->setCursor(1,3);
    pLcd->print("DISPOSAL");
    pLcd->setCursor(1,4);
    pLcd->print("CALIBRATING...");

}
void LCD::turnOff()
{
    pLcd->noDisplay();
    pLcd->noBacklight();
}

void LCD::initCursor()
{
    pLcd->clear();
    pLcd->setCursor(1, 0); 
}


void LCD::displayAwake()
{
    this->turnOn();
    this->initCursor();
    pLcd->print("PRESS OPEN TO");
    pLcd->setCursor(1,2);
    pLcd->print("ENTER WASTE");
}

void LCD::displayOpeningContainer()
{
    this->turnOn();
    this->initCursor();
    pLcd->print("OPENING");
}

void LCD::displayOpen()
{
    this->turnOn();
    this->initCursor();
    pLcd->print("PRESS CLOSE");
    pLcd->setCursor(1,2);
    pLcd->print("WHEN DONE");
}

void LCD::displayClosingContainer()
{
    this->turnOn();
    this->initCursor();
    pLcd->print("CLOSING");
}

void LCD::displayClose()
{
    this->turnOn();
    this->initCursor();
    pLcd->print("WASTE RECIVED");
}

void LCD::displayFull()
{
    this->turnOn();
    this->initCursor();
    pLcd->print("CONTAINER FULL");
}

void LCD::displayEmptingContainer()
{
    this->turnOn();
    this->initCursor();
    pLcd->print("EMPTYING THE");
    pLcd->setCursor(1,2);
    pLcd->print("CONTAINER");
}

void LCD::displayProblemDetected()
{
    this->turnOn();
    this->initCursor();
    pLcd->print("PROBLEM");
    pLcd->setCursor(1,2);
    pLcd->print("CONTAINER");
}

void LCD::displayRestore()
{
    this->turnOn();
    this->initCursor();
    pLcd->print("RESTORED");
}

