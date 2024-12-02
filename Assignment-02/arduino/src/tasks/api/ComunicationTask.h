#ifndef COMUNICATIONTASK_H
#define COMUNICATIONTASK_H

#include "Task.h"
#include "SWDSystem.h"


class ComunicationTask: public Task {
public:
    ComunicationTask(SWDSystem* machine);
     void tick();

private:
  void setState(int s);

  long elapsedTimeInState();

  void handleCommand(const String& command);


  void sendStatus(int status);


  double getWasteLevel();
  double getTemperature();     
    enum State { RECIVING_DATA, SENDING_DATA };  

    int currentState;
  long stateTimestamp;      
  bool justEntered;          
  SWDSystem* machine;
};


#endif 