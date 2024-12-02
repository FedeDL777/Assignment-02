#ifndef COMUNICATIONTASK_H
#define COMUNICATIONTASK_H

#include "Task.h"
#include "SWDSPlant.h"


class ComunicationTask: public Task {
public:
    ComunicationTask(SWDSPlant* machine);
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
  SWDSPlant* machine;
};


#endif 