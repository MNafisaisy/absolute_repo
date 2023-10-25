#include <Arduino.h>
#include <Wire.h>
#include "remote.h"
#include "telemetry.h"

Telemetry tele;
Input masuk;

void initialization();

void setup()
{
  Serial.begin(57600);
  Serial2.begin(57600);
  tele.begin();

  pinMode(18, OUTPUT);
  pinMode(5, OUTPUT);  
  pinMode(34, INPUT); // con
  pinMode(35, INPUT); // dump
  pinMode(15, INPUT); // right
  pinMode(12, INPUT); // left
  pinMode(2, OUTPUT);
  // pinMode(13, INPUT); // cam

  digitalWrite(18, LOW);
  digitalWrite(5, LOW);
}

unsigned long previousTime1 = 0;  // Store the previous time
unsigned long previousTime2 = 0;  // Store the previous time
const int interval1 = 1000; // Interval for Task 1 (1 second)
const int interval2 = 100; // Interval for Task 2 (0.1 seconds)
bool isReceive = 0;
bool trade = 1;

void loop()
{
  //status();     // Initialize

  unsigned long currentTime = millis();
  unsigned long currentTime1 = millis();
  if (currentTime - previousTime1 >= interval1) {
    int throttleRight;
    masuk.readRightTools(throttleRight);

    int throttleLeft;
    masuk.readLeftTools(throttleLeft);

    int cameraAngle;
    masuk.readCam(cameraAngle);

    bool signalLeft;
    masuk.readSr(signalLeft);
    String convertSignalLeft = signalLeft ? "ON" : "OFF"; 

    bool signalRight;
    masuk.readSl(signalRight);
    String convertSignalRight = signalRight ? "ON" : "OFF"; 

    bool conveyerIsON;
    masuk.readCon(conveyerIsON);
    String convertConveyer = conveyerIsON ? "ON" : "OFF"; 

    bool conveyerIsOFF;
    masuk.readDump(conveyerIsOFF);
    String convertConveyer2 = conveyerIsOFF ? "ON" : "OFF"; 

    char output[255];
    memset(output, 0, sizeof(output));
    snprintf(output, sizeof(output), 
            "%03d,%03d," 
            "%s,%s,%s," 
            "%03d,%s", 

            throttleLeft, throttleRight, 
            convertConveyer.c_str(), convertSignalLeft.c_str(), convertSignalRight.c_str(), 
            cameraAngle, convertConveyer2.c_str()
            );
    // char output[256] = "2123,2023,OFF,OFF,ON,453,OFF";
    Serial.println(output);
    Serial2.println(output);
    previousTime1 = currentTime;  // Update the previous time for Task 1
  }
  
  // if (currentTime1 - previousTime2 >= interval2) {
  //   /* Parse input from Car RATS */
  //   String data = tele.fetchData(Serial2, isReceive);
  //   if(isReceive) {
  //     Serial.println(data);
  //     tele.parseData(data);
  //     digitalWrite(2, trade);
  //     trade = !trade;
  //   }
  //   previousTime2 = currentTime1;  // Update the previous time for Task 2
  // }
}

void initialization()
{
  String kirim = "TURN ON RATS CAR";
  String terima = "";

  Serial.print(kirim);
  while (Serial.available() > 0)
  {
    char receivedChar = Serial.read();
    if (receivedChar == '\n' || receivedChar == '\r')
    {
      break; // Terminate the string when a newline or carriage return is received
    }
    terima += receivedChar;
  }
  if (terima != "RATS IS ON")
  {
    initialization();
  }
}
