#include "tasks/api/DetectorTask.h"
#include <Arduino.h>
#include "core/Logger.h"
#include "core/MsgService.h"

//distanza minima a cui il contenitore non viene considerato pieno
#define MIN_DIST 0.03
#define EMPTING_TIME 4000

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
        Serial.println("DistanceD:" + String(machine->getDistance()));
        if(machine->getDistance() <= MIN_DIST && !machine->asProblem() 
        && !machine->isEmpting() && machine->getDistance() > 0){
            Serial.println("FULL Detected");
            machine->full();
            setState(FULL);
        }
        else if(machine->isEmpting() && EMPTING_TIME < elapsedTimeInState()){
            machine->awake();
            setState(AWAKE);
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
        else if(machine->isAwake()){
            machine->full();
            setState(FULL);
        }
        
        break;
    case SLEEP:
        logOnce(F("[DT] Sleep"));
        /*
        if(!machine->isInSleep()){
            if(machine->getDistance() < MIN_DIST && !machine->asProblem()){
                machine->full();
                setState(FULL);
            }
            else{
                setState(AWAKE);
            }
        }
        */
               if(!machine->isInSleep()){
            if(machine->preSleepFull()){
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
                if(msg->getContent() == "EMPTY"){
            pressed = true;
            }
            delete msg;
        }

    }
    return pressed;
}
