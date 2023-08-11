#include <Arduino.h>
class Input
{
private:
    

public:
    Input(){}; //constructor
    
    void readRightTools(int &thr){
        thr=analogRead(15);
    }
    
    void readLeftTools(int &thl){
        thl=analogRead(12);
    }   
    
    void readCam(int &cam){
        cam=analogRead(13);
    }
    
    void readSr(bool &sr){
        sr=digitalRead(19);
    }

    void readSl(bool &sl){
        sl=digitalRead(14);
    }

    void readCon(bool &con){
        con=digitalRead(34);
    }

    void readDump(bool &dump){
        dump=digitalRead(35);
    }

};