#ifndef __SONAR__
#define __SONAR__

class Sonar{
    public:
        Sonar(int echoPin, int trigPin, float temperature);
        float getDistance();
        void setTemperature(float temp);
    private:
        int echoPin;
        int trigPin;
        double soundSpeed;
        int temperature;
};

#endif