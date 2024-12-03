#include "tasks/api/TempTask.h"
#include <Arduino.h>
#include "core/Logger.h"
#include "core/MsgService.h"

#define TIME_IN_PROBLEM_DETECTED 6000
#define MAX_TEMP 40
#define CHECKTEMP 1000
#define RESTORE_TIME 2000

TempTask::TempTask(SWDSystem *Machine):machine(Machine)
{
    currentTemperature = 20;
    tempSamples=0;
    avgTemp = 0;
    checkTime = millis();
    setState(NORMAL);
}

void TempTask::tick()
{
    
    machine->checkTemperature();
    avgTemp += machine->getTemperature();
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
    logOnce(F("[TT] Normal"));
    if(currentTemperature > MAX_TEMP){
        setState(PROBLEM_DETECTED);
    }
    if(elapsedTimeInState() > RESTORE_TIME && machine->isRestore()){
        machine->awake();
        setState(NORMAL);

    }
        break;
    case PROBLEM_DETECTED:
    logOnce(F("[TT] PROBLEM DETECTED"));
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
        logOnce(F("[TT] Problem"));
        if(checkRestoreButtonPressed() && !machine->isInSleep()){
            machine->restore();
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
      Logger.log(msg);
      justEntered = false;
    }
}

bool TempTask::checkRestoreButtonPressed()
{
    bool pressed = false;
    if(MsgService.isMsgAvailable()){
        logOnce(F("[TT] Message available"));
        Msg* msg = MsgService.receiveMsg();
        if(msg != NULL){
            Logger.log("Received message: " + msg->getContent());
                if(msg->getContent() == "RESTORE"){
            pressed = true;
            }
            delete msg;
        }

    }
    return pressed;
}
