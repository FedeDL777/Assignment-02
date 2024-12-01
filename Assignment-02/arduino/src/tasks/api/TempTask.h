#ifndef __TEMPTASK__
#define __TEMPTASK__


#include <Arduino.h>
#include "Task.h"
#include "SWDSPlant.h"
 
class TempTask: public Task{
    public:
    TempTask(SWDSPlant* machine);
    void tick();
    private:
    SWDSPlant* machine;
      void setState(int newState);
      long elapsedTimeInState();
      long elapsedTimeCheckTemp();
      void logOnce(const String &msg);

      enum
      {
          NORMAL,
          PROBLEM,
          PROBLEM_DETECTED
      };
      int currentState;
      long stateTimestamp;
      // arco di tempo prima di fare la media della dei valori
      long checkTime;
      // numero di temperature per checktime
      double tempSamples;
      // temperatura media temporanea
      double avgTemp;
      bool justEntered;
      double currentTemperature;
};


#endif