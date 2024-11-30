#ifndef __SWDS_PLANT__
#define __SWDS_PLANT__

#include <Arduino.h>
#include "devices/api/Button.h"
#include "devices/api/LCD.h"
#include "devices/api/Led.h"
#include "devices/api/Pir.h"
#include "devices/api/SensorTemp.h"
#include "devices/api/ServoMotor.h"
#include "devices/api/Sonar.h"

class SWDSPlant {
    public:
    SWDSPlant();
    void init();
    
    void awake();
    void awaking();
    void sleep();

    void openContainer();
    void closeContainer();
    

    void checkUserPir();
    void checkDistance();
    void checkTemperature();
    private:
        double curTemperature;
        double curDistance;
        bool userDetected;

        enum{
            AWAKE, OPENING_CONTAINER, OPEN, CLOSING_CONTAINER,
            CLOSE, FULL, PROBLEM_DETECTED, RESTORE,
            SLEEP, AWAKING

        } state;

    Led* greenLed;
    Led* redLed;
    Button* closeButton;
    Button* openButton;

    Sonar* Sonar;
    Pir* Pir;
    SensorTemp* sTemperature;
    ServoMotor* containerDoor; 
};

#endif