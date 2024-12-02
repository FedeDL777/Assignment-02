#include "core/MsgService.h"
#include "Arduino.h"
#include "tasks/api/ComunicationTask.h"

#define SENDING_DATA_TIMEOUT 500  // Timeout per inviare lo stato
#define EMPTY_COMMAND "EMPTY"
#define RESTORE_COMMAND "RESTORE"

#define MAXDIST 0.11
#define MINDIST 0.02
 

  ComunicationTask::ComunicationTask(SWDSystem *machine): machine(machine)
  {
    setState(WAIT);
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
    int wasteLevel = getWasteLevel();    // Implementa funzione di lettura livello
    int temperature = getTemperature();  // Implementa funzione di lettura temperatura
    String status = String("cw:st:") + String(statusMessage) + 
                     ":" + String(wasteLevel).substring(0, 5) + ":" + String(temperature).substring(0, 5);  
    MsgService.sendMsg(status);
  }

  double ComunicationTask::getWasteLevel()
  {
    machine->checkDistance();
       double temp =  machine->getDistance();
      return temp * ((MAXDIST - MINDIST)/MAXDIST) * 100;
  }

  double ComunicationTask::getTemperature()
  {
    machine->checkTemperature();
      return machine->getTemperature();
  }
