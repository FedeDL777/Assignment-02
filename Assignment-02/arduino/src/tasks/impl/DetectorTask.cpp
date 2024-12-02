#include "tasks/api/DetectorTask.h"
#include <Arduino.h>
#include "core/Logger.h"
#include "core/MsgService.h"

//distanza minima a cui il contenitore non viene considerato pieno
#define MIN_DIST 0.02

DetectorTask::DetectorTask(SWDSystem *Machine): machine(Machine)
{
    setState(AWAKE);
}

void DetectorTask::tick()
{
    machine->checkDistance();
    switch (currentState)
    {
    case AWAKE:
        logOnce(F("[DT] Awake"));
        if(machine->getDistance() < MIN_DIST && !machine->asProblem() 
        && !machine->isEmpting()){
            machine->full();
            setState(FULL);
        }
        else if(machine->isInSleep()){
            setState(SLEEP);
        }

        break;
    case FULL:
        logOnce(F("[DT] Full"));
        if(this->checkFullButtonPressed()){
            machine->emptingContainer();
            setState(AWAKE);
        }
        else if(machine->isInSleep()){
            setState(SLEEP);
        }
        
        break;
    case SLEEP:
        logOnce(F("[DT] Sleep"));
        if(!machine->isInSleep()){
            if(machine->getDistance() < MIN_DIST && !machine->preSleepProblem()){
                machine->full();
                setState(FULL);
            }
            else{
                setState(AWAKE);
            }
        }

        break;

    }
}

void DetectorTask::setState(int newState)
{
    currentState = newState;
    stateTimestamp = millis();
    justEntered = true;
}


long DetectorTask::elapsedTimeInState()
{
    return millis() - stateTimestamp;
}

void DetectorTask::logOnce(const String &msg)
{
    if (justEntered){
      Logger.log(msg);
      justEntered = false;
    }
}

bool DetectorTask::checkFullButtonPressed()
{
    bool pressed = false;
    if(MsgService.isMsgAvailable()){
        Msg* msg = MsgService.receiveMsg();
        if(msg != NULL){
            Logger.log("Received message: " + msg->getContent());
                if(msg->getContent() == "FULL"){
            pressed = true;
            }
            delete msg;
        }

    }
    return pressed;
}
