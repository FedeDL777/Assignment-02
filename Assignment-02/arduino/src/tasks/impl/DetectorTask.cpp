#include "tasks/api/DetectorTask.h"
#include <Arduino.h>
#include "core/Logger.h"

//distanza minima a cui il contenitore non viene considerato pieno
#define MIN_DIST 0.04

DetectorTask::DetectorTask(SWDSPlant *Machine): machine(Machine)
{
    setState(AWAKE);
}

void DetectorTask::tick()
{
    machine->checkDistance();
    switch (currentState)
    {
    case AWAKE:


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
        if(machine->isEmpting()){
            setState(AWAKE);
        }
        else if(machine->isInSleep()){
            setState(SLEEP);
        }
        
        break;
    case SLEEP:
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
      //Logger.log(msg);
      justEntered = false;
    }
}
