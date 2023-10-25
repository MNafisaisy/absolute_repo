#ifndef INTERFACE_H
#define INTERFACE_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class LCD {
private:
    LiquidCrystal_I2C lcd;

public:
    LCD() : lcd(0x27, 16, 2) {}

    void begin() {
        lcd.init();
        lcd.backlight();
    }

    void showStatusDirection(String direction) {
        lcd.setCursor(0, 0);
        lcd.print("s: ");
        lcd.setCursor(3, 0);
        lcd.print(direction);
    }

    void showStatusTrash(String isFull) {
        lcd.setCursor(0, 1);
        lcd.print("t: ");
        lcd.setCursor(3, 1);
        lcd.print(isFull);
    }

    void showStatusBattery(float adc) {
        lcd.clear(); // Clear the screen before printing battery status
        lcd.setCursor(0, 0);
        lcd.print("battery :");
        lcd.setCursor(0, 1);
        lcd.print(adc);
    }
};

#endif
