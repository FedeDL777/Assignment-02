#ifndef __SWDSYSTEM__
#define __SWDSYSTEM__

#include <Arduino.h>
#include "devices/api/Button.h"
#include "devices/api/LCD.h"
#include "devices/api/Led.h"
#include "devices/api/Pir.h"
#include "devices/api/SensorTemp.h"
#include "devices/api/ServoMotor.h"
#include "devices/api/Sonar.h"

class SWDSystem {
public:
    SWDSystem();
    void init();
    
    void awake();
    void converterForAwaking();
    void awaking();
    void sleep();
    void converterForSleep();
    void openContainer();
    void opened();
    void closeContainer();
    void closed();
    void full();
    void problemDetected();  
    void emptingContainer();
    void restore();

    bool preSleepFull();
    bool preSleepProblem();
    bool preSleepAwake();
    void setPreSleepFull();
    void setPreSleepProblem();
    void setPreSleepAwake();

    bool isAwake();
    bool isFull();
    bool asProblem();
    bool isInSleep();
    bool isOpening();
    bool isOpen();
    bool isClosing();
    bool isClose();  
    bool isEmpting();
    bool isRestore();


    void checkUserPir();
    void checkDistance();
    void checkTemperature();
    void openServo();
    void closeServo();
    void normalLed();
    void problemLed();


    bool getUserPresence();
    double getDistance();
    double getTemperature();

    
    private:
        double curTemperature;
        double curDistance;
        bool userDetected;

        enum{
            AWAKE, OPENING_CONTAINER, OPEN, CLOSING_CONTAINER,
            CLOSE, FULL, PROBLEM_DETECTED, RESTORE,
            SLEEP, EMPTING_CONTAINER

        } state;
        //stato che aveva la macchina prima di andare in stato di sleep
        enum{
            PREV_AWAKE, PREV_FULL, PREV_PROBLEM
        } preSleep;

    Led* greenLed;
    Led* redLed;

    ServoMotor* containerDoor;
    LCD* userConsole;
    Sonar* sSonar;
    Pir* sPir;
    SensorTemp* sTemperature;
    
};

#endif