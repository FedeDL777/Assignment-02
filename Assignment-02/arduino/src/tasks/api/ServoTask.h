#ifndef __SERVO_TASK__
#define __SERVO_TASK__

#include "Task.h"
#include "SWDSPlant.h"

class ServoTask: public Task{
    public: 
    ServoTask(SWDSPlant* sPlant);
    void tick();



private:
    SWDSPlant* machine;
    bool asProblem();
    void setState(int newState);
    long elapsedTimeInState();
    void logOnce(const String& msg);

  enum { AWAKE, SLEEP, OPENING_CONTAINER, OPEN,
            CLOSING_CONTAINER, CLOSE, PROBLEM};
    int currentState;
  long stateTimestamp;
  bool justEntered;
    Button* closeButton;
    Button* openButton;
};

#endif