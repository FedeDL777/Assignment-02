#include "core/MsgService.h"
#include "Arduino.h"
#include "tasks/api/ComunicationTask.h"

#define SENDING_DATA_TIMEOUT 500  // Timeout per inviare lo stato
#define EMPTY_COMMAND "EMPTY"
#define RESTORE_COMMAND "RESTORE"

#define MAXDIST 0.11
#define MINDIST 0.02
 

  ComunicationTask::ComunicationTask(SWDSystem *Machine): machine(Machine)
  {
    setState(WAIT);
    curDistance = MAXDIST;
  }
 

  void ComunicationTask::tick()
  {
  
    switch (currentState)
    {
    case WAIT:
        if(elapsedTimeInState() > SENDING_DATA_TIMEOUT){
            setState(SENDING_DATA);
        }
        break;
    case SENDING_DATA:
    int statusMessage = 0;
        if(machine->isAwake()){
            statusMessage = 0;
        }
        else if(machine->isFull()){
            statusMessage = 1;
        }
        else if(machine->asProblem()){
            statusMessage = 2;
        }
        else if(machine->isInSleep()){
            statusMessage = 3;
        }
        else if(machine->isOpen()){
            statusMessage = 4;
        }
        else if(machine->isClose()){
            statusMessage = 5;
        }
        else if(machine->isEmpting()){
            statusMessage = 6;
        }
        else if(machine->isRestore()){
            statusMessage = 7;
        }

        sendStatus(statusMessage);
        setState(WAIT);
        break;
    }
  }

  void ComunicationTask::setState(int s)
  {
    currentState = s;
    stateTimestamp = millis();
    justEntered = true;
  }
  long ComunicationTask::elapsedTimeInState()
  {
    return millis() - stateTimestamp;
  }


  void ComunicationTask::handleCommand(const String &command)
  {
  }

    void ComunicationTask::sendStatus(int statusMessage){
            
      curDistance = machine->getDistance();
    double wasteLevel = getWasteLevel();    // Implementa funzione di lettura livello
    double temperature = getTemperature();  // Implementa funzione di lettura temperatura
    String status = String("cw:st:") + String(statusMessage) + 
                     ":" + String(wasteLevel).substring(0, 5) + ":" + String(temperature).substring(0, 5);  
    MsgService.sendMsg(status);
  }

  double ComunicationTask::getWasteLevel()
  {
      return ((MAXDIST - curDistance)/(MAXDIST - MINDIST)) * 100;
  }

  double ComunicationTask::getTemperature()
  {
    machine->checkTemperature();
      return machine->getTemperature();
  }
