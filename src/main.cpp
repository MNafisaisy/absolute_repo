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
  Serial2.begin(115200);
  lcd.init();
  lcd.backlight();
  pinMode(18, OUTPUT);
  pinMode(5, OUTPUT);  
  pinMode(34, INPUT); // con
  pinMode(35, INPUT); // dump

  pinMode(15, INPUT); // right
  pinMode(12, INPUT); // left
  pinMode(13, INPUT); // cam
  digitalWrite(18, LOW);
  digitalWrite(5, LOW);
}

void loop()
{
  //status();     // Initialize
  
  /* Parse input from Car RATS */
  // String nemuSerial = "";
  // while (Serial.available())
  // {
  //   char receivedChar = Serial.read();
  //   nemuSerial += receivedChar;
  // }
  // parseNafis(nemuSerial);

  // lcd.setCursor(0, 0);
  // lcd.print("s: ");
  // lcd.setCursor(3, 0);
  // lcd.print(stat);

  // lcd.setCursor(0, 1);
  // lcd.print("t: ");
  // lcd.setCursor(3, 1);
  // lcd.print(ifull);

  // lcd.setCursor(6, 0);
  // lcd.print("battery :");
  // lcd.setCursor(6, 1);
  // lcd.print(ibatt);
  // lcd.clear();
  
  // lcd.backlight(); // test feature

  masuk.readRightTools(thr);
  masuk.readLeftTools(thl);
  masuk.readCam(cam);
  // masuk.readSr(sr);
  // masuk.readSl(sl);
  masuk.readCon(con);
  // con ? Serial.println("HIGH CON") : Serial.println("LOW CON");
  masuk.readDump(dump);
  // dump ? Serial.println("HIGH DUMP") : Serial.println("LOW DUMP");

  snprintf(output, sizeof(output), "%d", "%d", "%d", "%s", "%s", "%s", "%s", "%s", thr, thl, cam, sr, sl, con, dump, stat);
  Serial.print(thr); Serial.print("         ");
  Serial.print(thl); Serial.print("         ");
  Serial.print(cam); Serial.print("         ");
  Serial.print(con); Serial.print("         ");
  Serial.print(dump); Serial.println("         ");
  delay(1000);
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