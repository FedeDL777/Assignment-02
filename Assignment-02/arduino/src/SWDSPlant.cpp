#include "SWDSPlant.h"
#include "set-up.h"


SWDSPlant::SWDSPlant() : greenLed(nullptr), redLed(nullptr), 
                         closeButton(nullptr), openButton(nullptr), 
                         sSonar(nullptr), sPir(nullptr), 
                         sTemperature(nullptr), containerDoor(nullptr) 
                         {
                            
                         }

void SWDSPlant::init() {
    // Inizializzazione dei Led
    sLCD = new LCD();
    greenLed = new Led(GREEN_LED);
    redLed = new Led(RED_LED);

    // Inizializzazione dei Button
    closeButton = new Button(BUTTON_CLOSE);
    openButton = new Button(BUTTON_OPEN);

    // Inizializzazione del Sonar
    sSonar = new Sonar(SONAR_ECHO, SONAR_TRIG, 10000);

    // Inizializzazione del Pir
    sPir = new Pir(PIR_);

    // Inizializzazione del sensore di temperatura
    sTemperature = new SensorTemp(TEMP_);

    // Inizializzazione del servo motore
    containerDoor = new ServoMotor(SERVO_PIN);

    //logger
    this->sPir->calibrate();
    state = AWAKE;
    preSleep = PREV_AWAKE;
}


void SWDSPlant::awake()
{
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
    this->converterForSleep();
    state = SLEEP;
}

void SWDSPlant::openContainer()
{
    state = OPENING_CONTAINER;
}

void SWDSPlant::opened()
{
    state = OPEN;
}

void SWDSPlant::closeContainer()
{
    state = CLOSING_CONTAINER;
}

void SWDSPlant::closed()
{
    state = CLOSE;
}

void SWDSPlant::full()
{
    state = FULL;
}

void SWDSPlant::problemDetected()
{
    state = PROBLEM_DETECTED;
}

void SWDSPlant::emptingContainer()
{
    state = EMPTING_CONTAINER;
}

void SWDSPlant::restore()
{
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
bool SWDSPlant::isAwake()
{
    return state == AWAKE;
}
bool SWDSPlant::isAwake()
{
    return state == AWAKE;
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
