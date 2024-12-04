#include "tasks/api/ServoTask.h"
#include <Arduino.h>
#include "core/Logger.h"
#include "set-up.h"


#define CONTAINER_OPENED 10000
#define CONTAINER_CLOSING 4000
#define RESTORE_TIME 4000

ServoTask::ServoTask(SWDSystem *Machine): machine(Machine)
{
    setState(AWAKE);
    openButton = new Button(BUTTON_OPEN);
    closeButton = new Button(BUTTON_CLOSE);
}

void ServoTask::tick()

{
    switch (currentState)
    {
    case AWAKE:
        if(justEntered){
            machine->awake();
        }
        logOnce(F("[ST] Awake"));
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
        logOnce(F("[ST] Opening Container"));
        machine->opened();
        machine->openServo();
        setState(OPEN);
        break;


    case OPEN:
        logOnce(F("[ST] Open"));
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
        logOnce(F("[ST] Closing Container"));
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
        logOnce(F("[ST] Close"));
        if(asProblem()){
            setState(PROBLEM);
        }
        else if(elapsedTimeInState() > CONTAINER_CLOSING){
            machine->awake();//
            setState(AWAKE);
        }
        break;


    case PROBLEM:
        logOnce(F("[ST] Problem"));
        if(machine->isInSleep()){
            setState(SLEEP);
        }
        else if(!asProblem()){
            setState(RESTORED);
        }
        break;

    case RESTORED:
        logOnce(F("[ST] Restored"));
        if(elapsedTimeInState() > CONTAINER_CLOSING){
            machine->awake();//
            setState(AWAKE);
        }
        break;    
    case SLEEP:
        logOnce(F("[ST] Sleep"));
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
      Logger.log(msg);
      justEntered = false;
    }
}
