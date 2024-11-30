#ifndef __PIR__
#define __PIR__

class Pir {

    public:
        Pir(int pin);
        bool isDetected();
        void calibrate();
        void sync();
        long getLastSyncTime();



    private:
        bool present;
        int pin;
        long lastTimeSync;
};

#endif