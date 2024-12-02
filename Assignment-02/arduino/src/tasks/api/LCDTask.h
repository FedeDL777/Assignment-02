#ifndef __LCDTask__
#define __LCDTask__

#include "Task.h"
#include "SWDSystem.h"

class LCDTask: public Task{

    public:
    LCDTask(SWDSystem* machine);
    void tick();
    void init();
    private:
    SWDSystem* machine;
      void setState(int state);
      long elapsedTimeInState();
      void logOnce(const String& msg);


    int currentState;
    long stateTimestamp;
    bool justEntered;

};

#endif