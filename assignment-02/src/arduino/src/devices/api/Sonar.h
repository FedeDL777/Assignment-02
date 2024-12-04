#ifndef __SONAR__
#define __SONAR__

class Sonar{
    public:
        Sonar(int echoPin, int trigPin);
        float getDistance();
        void setTemperature(float temp);
        
    private:
        float getSoundSpeed(); 
        int echoPin;
        int trigPin;
        double soundSpeed;
        int temperature;
};

#endif