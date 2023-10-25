#ifndef telemetry
#define telemetry

#include <Arduino.h>
#include "interface.cpp"

class Telemetry{
private:
    LCD lcd;

public:
    Telemetry();
    void begin();
    String fetchData(HardwareSerial &Serial, bool &isReceive);
    void parseData(String data);
    void listCommand(String battery, String isTurnLeft, String isTurnRigt, String trash);
};

#endif