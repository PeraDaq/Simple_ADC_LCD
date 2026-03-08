#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);   // Change to 0x3F if your module uses that address

const int adcPin = A0;
const int ledPin = 8;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int adcValue = analogRead(adcPin);
  float voltage = adcValue * (5.0 / 1023.0);

  // turn the ledPin on
  digitalWrite(ledPin, HIGH);
  // stop the program for <sensorValue> milliseconds:
  delay(adcValue);
  // turn the ledPin off:
  digitalWrite(ledPin, LOW);
  // stop the program for <sensorValue> milliseconds:
  delay(adcValue);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("ADC: ");
  lcd.print(adcValue);

  lcd.setCursor(0, 1);
  lcd.print("Volt: ");
  lcd.print(voltage, 3);
  lcd.print(" V");

  // Teleplot over serial requires the ">" prefix.
  Serial.print(">adc:");
  Serial.println(adcValue);
  Serial.print(">volt:");
  Serial.println(voltage, 3);

  delay(200);
}
