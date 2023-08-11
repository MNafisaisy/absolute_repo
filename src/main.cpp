#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "remote.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

char output[256];
char parsingan[256];
String stat, ifull;
int thr, thl, cam, itungan;
bool dump, con, full, sr, sl;
float ibatt;

void parseNafis(String nemuSerial);
void status();
Input masuk;

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop()
{
  status();     // Initialize
  
  /* Parse input from Car RATS */
  String nemuSerial = "";
  while (Serial.available())
  {
    char receivedChar = Serial.read();
    if (receivedChar == '\n' || receivedChar == '\r')
    {
      break; // Terminate the string when a newline or carriage return is received
    }
    nemuSerial += receivedChar;
  }
  parseNafis(nemuSerial);

  lcd.setCursor(0, 0);
  lcd.print("s: ");
  lcd.setCursor(3, 0);
  lcd.print(stat);

  lcd.setCursor(0, 1);
  lcd.print("t: ");
  lcd.setCursor(3, 1);
  lcd.print(ifull);

  lcd.setCursor(6, 0);
  lcd.print("battery :");
  lcd.setCursor(6, 1);
  lcd.print(ibatt);
  lcd.clear();
  
  lcd.backlight(); // test feature

  masuk.readRightTools(thr);
  masuk.readLeftTools(thl);
  masuk.readCam(cam);
  masuk.readSr(sr);
  masuk.readSl(sl);
  masuk.readCon(con);
  masuk.readDump(dump);
  
  snprintf(output, sizeof(output), "%d", "%d", "%d", "%s", "%s", "%s", "%s", "%s", thr, thl, cam, sr, sl, con, dump, stat);
  Serial.print(output);
}

void parseData(String conveyer, String dump, String batt, String full) {
  ifull = full;
  ibatt = batt.toFloat();

  full = ifull == "ON" ? true : false;
}

void parseNafis(String nemuSerial)
{
  int itungkata = 0;
  String hasilBaca[256];

  for (int counter = 0; counter <= nemuSerial.length(); counter++)
  {
    if (parsingan[counter] != ',')
    {
      hasilBaca[itungkata] += parsingan[counter];
      hasilBaca[itungkata].trim();
    }
    else
    {
      itungkata++;
    }
  }
  parseData(hasilBaca[0],hasilBaca[1],hasilBaca[2],hasilBaca[3]);
}

void status()
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
    status();
  }
}