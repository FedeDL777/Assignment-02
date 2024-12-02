#ifndef __SERVO_TASK__
#define __SERVO_TASK__

#include "Task.h"
#include "SWDSystem.h"

class ServoTask: public Task{
    public: 
    ServoTask(SWDSystem* machine);
    void tick();



private:
    SWDSystem* machine;
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