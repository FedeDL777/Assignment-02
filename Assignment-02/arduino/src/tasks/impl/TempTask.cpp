#include "tasks/api/TempTask.h"
#include <Arduino.h>
#include "core/Logger.h"

#define TIME_IN_PROBLEM_DETECTED 6000
#define MAX_TEMP 32
#define CHECKTEMP 1000

TempTask::TempTask(SWDSystem *Machine):machine(Machine)
{
    currentTemperature = 20;
    tempSamples=0;
    avgTemp = 0;
    checkTime = millis();
}

void TempTask::tick()
{
    machine->checkTemperature();
    avgTemp =+ machine->getTemperature();
    tempSamples++;
    if(elapsedTimeCheckTemp() > CHECKTEMP){
        currentTemperature = avgTemp / tempSamples;
        tempSamples=0;
        avgTemp = 0;
        checkTime = millis();
    }
    switch (currentState)
    {
    case NORMAL:
    if(currentTemperature > MAX_TEMP){
        setState(PROBLEM_DETECTED);
    }
        break;
    case PROBLEM_DETECTED:
    if(currentTemperature < MAX_TEMP){
        setState(NORMAL);
    }
    else if(elapsedTimeInState() > TIME_IN_PROBLEM_DETECTED){
        setState(PROBLEM);
        if(machine->isInSleep()){
            machine->setPreSleepProblem();
        }
        else{
            machine->problemDetected();
        }

    }
        break;
    case PROBLEM:
        if(!machine->asProblem() && !machine->isInSleep()){
            setState(NORMAL);
        }  
        break;
        
    }
}

void TempTask::setState(int newState)
{
    currentState = newState;
    stateTimestamp = millis();
    justEntered = true;
}

long TempTask::elapsedTimeInState()
{
    return millis() - stateTimestamp;
}

long TempTask::elapsedTimeCheckTemp()
{
    return millis() - checkTime;
}

void TempTask::logOnce(const String &msg)
{
        if (justEntered){
      //Logger.log(msg);
      justEntered = false;
    }
}
