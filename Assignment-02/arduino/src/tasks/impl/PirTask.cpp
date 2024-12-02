#include "tasks/api/PirTask.h"
#include <Arduino.h>
#include "core/Logger.h"

#define MAX_INACTIVITY_TIME 10000

PirTask::PirTask(SWDSystem *Machine): machine(Machine)
{
    setState(AWAKE);
}

void PirTask::tick()
{
    machine->checkUserPir();
    switch (currentState)
    {
    case AWAKE:
        logOnce(F("[PT] Awake"));
        if(machine->getUserPresence()){
            setState(AWAKE);
        }
        if(elapsedTimeInState() > MAX_INACTIVITY_TIME){
            setState(SLEEP);
            machine->sleep();
        }
        if(!machine->isAwake()){
            checkState();
        }
        break;
    case FULL:
        logOnce(F("[PT] Full"));
        if(machine->getUserPresence()){
            setState(FULL);
        }
        if(elapsedTimeInState() > MAX_INACTIVITY_TIME){
            machine->sleep();
            setState(SLEEP);
        }
        if(!machine->isFull()){
            checkState();
        }
        break;
    case PROBLEM:
        logOnce(F("[PT] Problem"));
            if(machine->getUserPresence()){
            setState(PROBLEM);
        }
        if(elapsedTimeInState() > MAX_INACTIVITY_TIME){
            machine->sleep();
            setState(SLEEP);
        }
        if(!machine->asProblem()){
            checkState();
        }
        break;
    case SLEEP:
        logOnce(F("[PT] Sleep"));
        machine->checkUserPir();
        if(machine->getUserPresence()){
            machine->awaking();
            checkPreSleepState();
        }
        break;
    case BLOCKED:
    checkState();
        break;
    }
}
void PirTask::checkState()
{
    if(machine->isAwake()){
        setState(AWAKE);
    }
    else if(machine->asProblem()){
        setState(PROBLEM);
    }
    else if(machine->isFull()){
        setState(FULL);
    }
    else{
        setState(BLOCKED);
    }
}
void PirTask::checkPreSleepState()
{
    if(machine->preSleepAwake()){
        setState(AWAKE);
    }
    else if(machine->preSleepProblem()){
        setState(PROBLEM);
    }
    else if(machine->preSleepFull()){
        setState(FULL);
    }
    else{
        setState(BLOCKED);
    }
}

void PirTask::setState(int newState)
{
    currentState = newState;
    stateTimestamp = millis();
    justEntered = true;
}

long PirTask::elapsedTimeInState()
{
    return millis() - stateTimestamp;
}

void PirTask::logOnce(const String &msg)
{
            if (justEntered){
      Logger.log(msg);
      justEntered = false;
    }
}
