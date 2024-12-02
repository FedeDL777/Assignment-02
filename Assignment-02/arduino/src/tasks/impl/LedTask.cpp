#include "tasks/api/LedTask.h"
#include <Arduino.h>
#include "core/Logger.h"

LedTask::LedTask(SWDSystem *Machine): machine(Machine)
{
    machine->normalLed();
    setState(NORMAL);
}

void LedTask::tick()
{
switch (currentState){
case NORMAL:
        logOnce(F("[LT] Normal"));
        if(machine->asProblem() || machine->isFull()){
            machine->problemLed();
            setState(PROBLEM);
        }

    break;

case PROBLEM:
        logOnce(F("[LT] Problem"));
        if(!machine->asProblem() && !machine->isFull() && !machine->isInSleep()){
            machine->normalLed();
            setState(NORMAL);
        }
    break;
}
}

void LedTask::setState(int newState)
{
    currentState = newState;
    stateTimestamp = millis();
    justEntered = true;
}

long LedTask::elapsedTimeInState()
{
    return millis() - stateTimestamp;
}

void LedTask::logOnce(const String &msg)
{
    if (justEntered){
      Logger.log(msg);
      justEntered = false;
    }
}
