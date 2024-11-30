#ifndef __TASK__ 
#define __TASK__

class Task
{
private:
    long period;
    bool active;
    bool periodic;
    bool completed;
    long timeElapsed;
public:
    Task();
    void setUp(int P){
        period = P;
        active = true;
        completed = false;
        timeElapsed = 0;
        period = true;
    }
    void setUp(){
        period = 0;
        active = true;
        completed = false;
        timeElapsed = 0;
        period = false;
    }
    virtual void tick() = 0;

    bool updateAndCheckTime(int basePeriod) {
    timeElapsed += basePeriod;
    if (timeElapsed >= period) {
        timeElapsed = 0; // reset relativo per migliorare precisione
        return true;
    }
    return false;
    }
    void setComplete(){
        completed = true;
    }
    bool isCompleted(){
        return completed;
    }
    bool isPeriodic(){
        return periodic;
    }
    void setActive(){
        active = (active =! true);
    }
        void setActive(bool set){
        active = set;
    }

};


#endif