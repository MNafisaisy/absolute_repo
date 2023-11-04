#include "telemetry.h"

Telemetry::Telemetry():lcd(LCD()){}

void Telemetry::begin()
{
    lcd.begin();
}

String Telemetry::fetchData(HardwareSerial &Serial, bool &isReceive)
{
    String result;
    while(Serial.available() > 0) 
    {
        result += (char)Serial.read();
        isReceive = true;
    }
    result.trim();
    return result;
}

void Telemetry::parseData(String data)
{
    int itungkata = 0;
    String hasilBaca[data.length() + 1];
    char tempHasil[data.length() + 1];

    strcpy(tempHasil, data.c_str());
    for (int counter = 0; counter <= data.length(); counter++)
    {
        if (tempHasil[counter] != ',')
        {
            hasilBaca[itungkata] += tempHasil[counter];
            hasilBaca[itungkata].trim();
        }
        else
        {
            itungkata++;
        }
    }
    listCommand(hasilBaca[0],hasilBaca[1],hasilBaca[2],hasilBaca[3]);
}

void Telemetry::listCommand(String battery, String isTurnLeft, String isTurnRight, String trash)
{
    // lcd.showStatusBattery(battery.toFloat());
    // isTurnLeft == "YES" ? lcd.showStatusDirection(isTurnLeft) : lcd.showStatusDirection(isTurnRight); 
    // lcd.showStatusTrash(trash);  
}