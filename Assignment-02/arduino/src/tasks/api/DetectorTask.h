#ifndef __DETECTOR_TASK__
#define __DETECTOR_TAST__

#include "Task.h"
#include "SWDSystem.h"

class DetectorTask: public Task{

    public:
    DetectorTask(SWDSystem* machine);
    void tick();
    private:
    SWDSystem* machine;
      void setState(int newState);
      long elapsedTimeInState();
      void logOnce(const String& msg);

  enum { AWAKE, SLEEP, FULL};
    int currentState;
  long stateTimestamp;
  bool justEntered;

};

#endif