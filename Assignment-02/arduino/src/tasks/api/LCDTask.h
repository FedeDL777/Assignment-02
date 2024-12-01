#ifndef __LCDTask__
#define __LCDTask__

#include "Task.h"
#include "SWDSPlant.h"

class LCDTask: public Task{

    public:
    LCDTask(SWDSPlant* machine);
    void tick();
    void init();
    private:
    SWDSPlant* machine;
      void setState(int state);
      long elapsedTimeInState();
      void logOnce(const String& msg);


    int currentState;
    long stateTimestamp;
    bool justEntered;

};

#endif