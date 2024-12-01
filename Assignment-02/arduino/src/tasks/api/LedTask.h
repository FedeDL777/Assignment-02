#ifndef __LEDTASK__
#define __LEDTASK__


#include <Arduino.h>
#include "Task.h"
#include "SWDSPlant.h"
 
class LedTask: public Task{
    public:
    LedTask(SWDSPlant* machine);
    void tick();
    private:
    SWDSPlant* machine;
      void setState(int newState);
      long elapsedTimeInState();
      void logOnce(const String& msg);

  enum { NORMAL, PROBLEM};
    int currentState;
  long stateTimestamp;
  bool justEntered;
};


#endif