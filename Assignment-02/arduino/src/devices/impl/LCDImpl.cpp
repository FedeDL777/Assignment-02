#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "set-up.h"
#include  "devices/api/LCD.h"


LCD::LCD()
{
    pLcd = new  LiquidCrystal_I2C(0x27,20,4);
}
void LCD::setup()
{
    pLcd->init();
  pLcd->backlight();
  pLcd->noDisplay();
}



void LCD::turnOn()
{
      pLcd->display();
  pLcd->clear();
}
void LCD::turnOff()
{
    pLcd->noDisplay();
}

void LCD::initCursor()
{
    pLcd->clear();
    pLcd->setCursor(1, 0); 
}


void LCD::displayAwake()
{
    this->initCursor();
    pLcd->print("PRESS OPEN TO");
    pLcd->setCursor(1,2);
    pLcd->print("ENTER WASTE");
}

void LCD::displayOpeningContainer()
{
    this->initCursor();
    pLcd->print("OPENING");
}

void LCD::displayOpen()
{
    this->initCursor();
    pLcd->print("PRESS CLOSE");
    pLcd->setCursor(1,2);
    pLcd->print("WHEN DONE");
}

void LCD::displayClosingContainer()
{
    this->initCursor();
    pLcd->print("CLOSING");
}

void LCD::displayClose()
{
    this->initCursor();
    pLcd->print("WASTE RECIVED");
}

void LCD::displayFull()
{
    this->initCursor();
    pLcd->print("CONTAINER FULL");
}

void LCD::displayEmptingContainer()
{
    this->initCursor();
    pLcd->print("EMPTYING THE");
    pLcd->setCursor(1,2);
    pLcd->print("CONTAINER");
}

void LCD::displayProblemDetected()
{
    this->initCursor();
    pLcd->print("PROBLEM");
    pLcd->setCursor(1,2);
    pLcd->print("CONTAINER");
}

void LCD::displayRestore()
{
    this->initCursor();
    pLcd->print("RESTORED");
}

