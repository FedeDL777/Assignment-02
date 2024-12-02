#include "SWDSystem.h"
#include "set-up.h"
#include "core/Logger.h"

SWDSystem::SWDSystem() {
                            
}

void SWDSystem::init() {
    // Inizializzazione dei Led
    sLCD = new LCD();
    greenLed = new Led(GREEN_LED);
    redLed = new Led(RED_LED);

    // Inizializzazione del Sonar
    sSonar = new Sonar(SONAR_ECHO, SONAR_TRIG);

    // Inizializzazione del Pir
    sPir = new Pir(PIR_PIN);

    // Inizializzazione del sensore di temperatura
    sTemperature = new SensorTemp(TEMP_);

    // Inizializzazione del servo motore
    containerDoor = new ServoMotor(SERVO_MOTOR);

    //logger
    Logger.log("Calibrating sensors...");
    this->sPir->calibrate();
    state = AWAKE;
    preSleep = PREV_AWAKE;
    this->sLCD->setup();
    //this->sLCD->turnOn();
}


void SWDSystem::awake()
{
    this->sLCD->displayAwake();
    state = AWAKE;
}

void SWDSystem::converterForAwaking(){
    switch (preSleep)
    {
    case PREV_FULL:
        state = FULL;
        break;
    case PREV_PROBLEM:
        state = PROBLEM_DETECTED;
        break;
    default:
        state = AWAKE;
        break;
    }
}
void SWDSystem::awaking()
{
    this->sLCD->turnOn();
    converterForAwaking();
}
void SWDSystem::converterForSleep(){
    if(this->asProblem()){
        preSleep = PREV_PROBLEM;
    }
    else if(this->isFull()){
        preSleep = PREV_FULL;
    }
    else{
        preSleep = PREV_AWAKE;
    }
}

void SWDSystem::sleep()
{
    this->sLCD->turnOff();
    this->converterForSleep();
    state = SLEEP;
}

void SWDSystem::openContainer()
{
    this->sLCD->displayOpeningContainer();
    state = OPENING_CONTAINER;
}

void SWDSystem::opened()
{
    this->sLCD->displayOpen();
    state = OPEN;
}

void SWDSystem::closeContainer()
{
    this->sLCD->displayClosingContainer();
    state = CLOSING_CONTAINER;
}


void SWDSystem::closed()
{
    this->sLCD->displayClose();
    state = CLOSE;
}

void SWDSystem::full()
{
    this->sLCD->displayFull();
    state = FULL;
}

void SWDSystem::problemDetected()
{
    this->sLCD->displayProblemDetected();
    state = PROBLEM_DETECTED;
}

void SWDSystem::emptingContainer()
{
    this->sLCD->displayEmptingContainer();
    state = EMPTING_CONTAINER;
}

void SWDSystem::restore()
{
    this->sLCD->displayRestore();
    state = RESTORE;
}


bool SWDSystem::preSleepFull()
{
    return preSleep == PREV_FULL;
}
bool SWDSystem::preSleepProblem()
{
    return preSleep == PREV_PROBLEM;
}
bool SWDSystem::preSleepAwake()
{
    return preSleep == PREV_AWAKE;
}
void SWDSystem::setPreSleepFull()
{
    preSleep = PREV_FULL;
}
void SWDSystem::setPreSleepProblem()
{
    preSleep = PREV_PROBLEM;
}
void SWDSystem::setPreSleepAwake()
{
    preSleep = PREV_AWAKE;
}
bool SWDSystem::isAwake()
{
    return state == AWAKE;
}
bool SWDSystem::isFull()
{
    return state == FULL;
}

bool SWDSystem::asProblem()
{
    return state == PROBLEM_DETECTED;
}

bool SWDSystem::isInSleep()
{
    return state == SLEEP;
}

bool SWDSystem::isOpening()
{
    return state == OPENING_CONTAINER;
}

bool SWDSystem::isOpen()
{
    return state == OPEN;
}

bool SWDSystem::isClosing()
{
    return state == CLOSING_CONTAINER;
}

bool SWDSystem::isClose()
{
    return state == CLOSE;
}

bool SWDSystem::isEmpting()
{
    return state == EMPTING_CONTAINER;
}

bool SWDSystem::isRestore()
{
    return state == RESTORE;
}

void SWDSystem::checkUserPir()
{
    this->sPir->sync();
    userDetected = this->sPir->isDetected();
}

void SWDSystem::checkDistance()
{
    this->checkTemperature();
    this->sSonar->setTemperature(this->sTemperature->getTemperature());
    curDistance = this->sSonar->getDistance();
}

void SWDSystem::checkTemperature()
{
    this->curTemperature = this->sTemperature->getTemperature();
}

bool SWDSystem::getUserPresence()
{
    return userDetected;
}

double SWDSystem::getDistance()
{
    return curDistance;
}

double SWDSystem::getTemperature()
{
    return curTemperature;
}

void SWDSystem::openServo(){
    containerDoor->on();
    containerDoor->setPosition(90);
}

void SWDSystem::closeServo(){
    containerDoor->setPosition(0);
}
void SWDSystem::normalLed()
{
    greenLed->switchOn();
    redLed->switchOff();
}

void SWDSystem::problemLed()
{
    greenLed->switchOff();
    redLed->switchOn();
}
