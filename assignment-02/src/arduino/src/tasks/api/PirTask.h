#ifndef __PIRTASK__
#define __PIRTASK__

#include <Arduino.h>
#include "Task.h"
#include "SWDSystem.h"

class PirTask: public Task{

    public:
    PirTask(SWDSystem* machine);
    void tick();

private:
    SWDSystem* machine;
      void setState(int state);
      long elapsedTimeInState();
      void logOnce(const String& msg);
    void checkState();
    void checkPreSleepState();

  enum { AWAKE, SLEEP, FULL, PROBLEM, BLOCKED};
    int currentState;
  long stateTimestamp;
  bool justEntered;

};

#endif