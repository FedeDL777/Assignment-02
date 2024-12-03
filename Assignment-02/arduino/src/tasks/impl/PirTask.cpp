#include "tasks/api/PirTask.h"
#include <Arduino.h>
#include "core/Logger.h"
#include <avr/sleep.h>

#define MAX_INACTIVITY_TIME 10000

void wakeUp()
{}

PirTask::PirTask(SWDSystem *Machine): machine(Machine)
{
    attachInterrupt(digitalPinToInterrupt(PIR_PIN), wakeUp, RISING);
    setState(AWAKE);
}

void PirTask::tick()
{
    machine->checkUserPir();
    switch (currentState)
    {
    case AWAKE:
        logOnce(F("[PT] Awake"));
        if(!machine->isAwake()){
            checkState();
        }
        if(machine->getUserPresence()){
            setState(AWAKE);
        }
        if(elapsedTimeInState() > MAX_INACTIVITY_TIME){
            setState(SLEEP);
            
        }
        break;
    case FULL:
        logOnce(F("[PT] Full"));
        if(machine->getUserPresence()){
            setState(FULL);
        }
        if(!machine->isFull()){
            checkState();
        }
        if(elapsedTimeInState() > MAX_INACTIVITY_TIME){
            machine->sleep();
            setState(SLEEP);
        }
        break;
    case PROBLEM:
        logOnce(F("[PT] Problem"));
            if(machine->getUserPresence()){
            setState(PROBLEM);
        }
        if(!machine->asProblem()){
            checkState();
        }
        if(elapsedTimeInState() > MAX_INACTIVITY_TIME){
            machine->sleep();
            setState(SLEEP);
        }
        break;
    case SLEEP:
        logOnce(F("[PT] Sleep"));
        machine->sleep();
        //
        delay(100);
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable();
        sleep_mode();
        sleep_disable();
        machine->awaking();
        checkPreSleepState();
        break;
    case BLOCKED:
        logOnce(F("[PT] Blocked"));
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
