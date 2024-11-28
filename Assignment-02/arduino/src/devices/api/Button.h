#ifndef __BUTTON__
#define __BUTTON__

class Button{
public:
    Button(int pin);
    
    
   // bool clicked();
    void sync();
    long getLastSyncTime();
    bool isPressed();
protected:
    void updateSyncTime(long time);

private:
    long lastTimeSync;
    int pin;
    bool pressed;
    //bool clicked;
};




#endif 
