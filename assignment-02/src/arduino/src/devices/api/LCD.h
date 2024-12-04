#ifndef __LCD__
#define __LCD__
#include <LiquidCrystal_I2C.h>
#include "set-up.h"
class LCD{
    public:
    LCD();
    void setup();

    void turnOff();
    void turnOn();
    void displayWelcome();
    void displayAwake();
    void displayOpeningContainer();
    void displayOpen();
    void displayClosingContainer();
    void displayClose();
    void displayFull();
    void displayEmptingContainer();
    void displayProblemDetected();
    void displayRestore();
    private:
        LiquidCrystal_I2C* pLcd; 
        void initCursor();
};

#endif