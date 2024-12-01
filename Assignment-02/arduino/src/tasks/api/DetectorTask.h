#ifndef __DETECTOR_TASK__
#define __DETECTOR_TAST__

#include "Task.h"
#include "SWDSPlant.h"

class DetectorTask: public Task{

    public:
    DetectorTask(SWDSPlant* machine);
    void tick();
    private:
    SWDSPlant* machine;
      void setState(int state);
      long elapsedTimeInState();
      void logOnce(const String& msg);

  enum { AWAKE, SLEEP, FULL};
    int currentState;
  long stateTimestamp;
  bool justEntered;

};

#endif