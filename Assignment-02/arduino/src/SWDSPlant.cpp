#include "SWDSPlant.h"
#include "set-up.h"


SWDSPlant::SWDSPlant() : greenLed(nullptr), redLed(nullptr), 
                          
                         sSonar(nullptr), sPir(nullptr), 
                         sTemperature(nullptr), containerDoor(nullptr) 
                         {
                            
                         }

void SWDSPlant::init() {
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
    this->sPir->calibrate();
    state = AWAKE;
    preSleep = PREV_AWAKE;
    this->sLCD->setup();
    this->sLCD->turnOn();
}


void SWDSPlant::awake()
{
    this->sLCD->displayAwake();
    state = AWAKE;
}

void SWDSPlant::converterForAwaking(){
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
void SWDSPlant::awaking()
{
    this->sLCD->turnOn();
    converterForAwaking();
}
void SWDSPlant::converterForSleep(){
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

void SWDSPlant::sleep()
{
    this->sLCD->turnOff();
    this->converterForSleep();
    state = SLEEP;
}

void SWDSPlant::openContainer()
{
    this->sLCD->displayOpeningContainer();
    state = OPENING_CONTAINER;
}

void SWDSPlant::opened()
{
    this->sLCD->displayOpen();
    state = OPEN;
}

void SWDSPlant::closeContainer()
{
    this->sLCD->displayClosingContainer();
    state = CLOSING_CONTAINER;
}


void SWDSPlant::closed()
{
    this->sLCD->displayClose();
    state = CLOSE;
}

void SWDSPlant::full()
{
    this->sLCD->displayFull();
    state = FULL;
}

void SWDSPlant::problemDetected()
{
    this->sLCD->displayProblemDetected();
    state = PROBLEM_DETECTED;
}

void SWDSPlant::emptingContainer()
{
    this->sLCD->displayEmptingContainer();
    state = EMPTING_CONTAINER;
}

void SWDSPlant::restore()
{
    this->sLCD->displayRestore();
    state = RESTORE;
}


bool SWDSPlant::preSleepFull()
{
    return preSleep == PREV_FULL;
}
bool SWDSPlant::preSleepProblem()
{
    return preSleep == PREV_PROBLEM;
}
bool SWDSPlant::preSleepAwake()
{
    return preSleep == PREV_AWAKE;
}
void SWDSPlant::setPreSleepFull()
{
    preSleep = PREV_FULL;
}
void SWDSPlant::setPreSleepProblem()
{
    preSleep = PREV_PROBLEM;
}
void SWDSPlant::setPreSleepAwake()
{
    preSleep = PREV_AWAKE;
}
bool SWDSPlant::isAwake()
{
    return state == AWAKE;
}
bool SWDSPlant::isFull()
{
    return state == FULL;
}

bool SWDSPlant::asProblem()
{
    return state == PROBLEM_DETECTED;
}

bool SWDSPlant::isInSleep()
{
    return state == SLEEP;
}

bool SWDSPlant::isOpening()
{
    return state == OPENING_CONTAINER;
}

bool SWDSPlant::isOpen()
{
    return state == OPEN;
}

bool SWDSPlant::isClosing()
{
    return state == CLOSING_CONTAINER;
}

bool SWDSPlant::isClose()
{
    return state == CLOSE;
}

bool SWDSPlant::isEmpting()
{
    return state == EMPTING_CONTAINER;
}

bool SWDSPlant::isRestore()
{
    return state == RESTORE;
}

void SWDSPlant::checkUserPir()
{
    this->sPir->sync();
    userDetected = this->sPir->isDetected();
}

void SWDSPlant::checkDistance()
{
    this->sSonar->setTemperature(this->sTemperature->getTemperature());
    curDistance = this->sSonar->getDistance();
}

void SWDSPlant::checkTemperature()
{
    this->curTemperature = this->sTemperature->getTemperature();
}

bool SWDSPlant::getUserPresence()
{
    return userDetected;
}

double SWDSPlant::getDistance()
{
    return curDistance;
}

double SWDSPlant::getTemperature()
{
    return curTemperature;
}

void SWDSPlant::openServo(){
    mServo->on();
    mServo->setPosition(90);
}

void SWDSPlant::closeServo(){
    mServo->setPosition(0);
}
void SWDSPlant::normalLed()
{
    greenLed->switchOn();
    redLed->switchOff();
}

void SWDSPlant::problemLed()
{
    greenLed->switchOff();
    redLed->switchOn();
}
