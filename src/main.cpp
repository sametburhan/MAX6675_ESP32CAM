#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "MAX6675.h"

#define SDA 15
#define SCL 14
LiquidCrystal_I2C lcd(0x27, 16, 2);

int thermoDO = 4;
int thermoCS = 2;
int thermoCLK = 13;

MAX6675 thermocouple;

void setup() {
  Wire.begin(SDA, SCL);
  thermocouple.begin(thermoCLK, thermoCS, thermoDO);

  lcd.init();
  lcd.clear();
  lcd.backlight();

  lcd.setCursor(0,1);
  lcd.print("Baslatildi");
}

void loop ()
{
  int status = thermocouple.read();
  if (status != STATUS_OK)
  {
    lcd.setCursor(0,1);
    lcd.print("ERROR!");
  }

  lcd.setCursor(0,0);
  lcd.print(thermocouple.getTemperature());
  lcd.print(" C");
  delay(1000);
}