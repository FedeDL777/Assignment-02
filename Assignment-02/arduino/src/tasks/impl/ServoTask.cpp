#include "tasks/api/ServoTask.h"
#include <Arduino.h>
#include "core/Logger.h"



#define CONTAINER_OPENED 10000

ServoTask::ServoTask(SWDSPlant *Machine): machine(Machine), closeButton(nullptr), openButton(nullptr)
{
        // Inizializzazione dei Button
    closeButton = new Button(BUTTON_CLOSE);
    openButton = new Button(BUTTON_OPEN);

    setState(AWAKE);
}

void ServoTask::tick()
{
    switch (currentState)
    {
    case AWAKE:
        if(machine->isInSleep()){
            setState(SLEEP);
        }
        openButton->sync();
        if(openButton->isPressed() && machine->isAwake()){
            machine->openContainer();
            setState(OPENING_CONTAINER);
        }
        break;


    case OPENING_CONTAINER:
        machine->opened();
        machine->openServo();
        setState(OPEN);
        break;


    case OPEN:
    //chiusura per Problema
        if(asProblem()){
            setState(CLOSING_CONTAINER);
        }
        //chiusura per bottone
        closeButton->sync();
        if(closeButton->isPressed() && machine->isOpen()){
            machine->closeContainer();
            setState(CLOSING_CONTAINER);
        }
        //chiusura per timer
        else if(elapsedTimeInState() > CONTAINER_OPENED && machine->isOpen()){
            machine->closeContainer();
            setState(CLOSING_CONTAINER);
        }
        //prolungamento dell'apertura
        openButton->sync();
        if(openButton->isPressed()){
            setState(OPEN);
        }
        break;

    
    case CLOSING_CONTAINER:
        if(asProblem()){
            setState(CLOSE);
        }
        else{
            setState(CLOSE);
            machine->closed();
        }
        machine->closeServo();
        break;


    case CLOSE:
        if(asProblem()){
            setState(PROBLEM);
        }
        else{
            machine->awake();
            setState(AWAKE);
        }
        break;


    case PROBLEM:
        if(machine->isInSleep()){
            setState(SLEEP);
        }
        else if(!asProblem()){
            setState(AWAKE);
        }
        break;

        
    case SLEEP:
        if(!machine->isInSleep() && (machine->preSleepFull() || machine->preSleepProblem())){
            setState(PROBLEM);
        }
        else if(!machine->isInSleep()){
            setState(AWAKE);
        }
        break;
    }
}
bool ServoTask::asProblem(){
    return machine->asProblem() || machine->isFull();
}

void ServoTask::setState(int newState)
{
    currentState = newState;
    stateTimestamp = millis();
    justEntered = true;
}

long ServoTask::elapsedTimeInState()
{
    return millis() - stateTimestamp;
}

void ServoTask::logOnce(const String &msg)
{
        if (justEntered){
      //Logger.log(msg);
      justEntered = false;
    }
}
