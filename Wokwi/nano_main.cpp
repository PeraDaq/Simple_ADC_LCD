/* This is an example of using the LiquidCrystal library to display the value of an analog input on an LCD.
 The built-in LED is also used to indicate the reading by blinking at a rate proportional to the analog value.*/

// Include the necessary libraries
#include <Arduino.h>
#include <LiquidCrystal.h>

// RS=12, E=11, D4=5, D5=4, D6=3, D7=2
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define the analog pin to read from
const int adcPin = A0;
const int ledPin = 8;

// The setup function runs once when you press reset or power the board
void setup() {
  // Initialize the LCD and set up the built-in LED pin
  lcd.begin(16, 2);
  // Clear the LCD screen
  lcd.clear();

  // Set the built-in LED pin as an output
  pinMode(ledPin, OUTPUT);
}

// The loop function runs over and over again forever
void loop() {
  // Read the value from the analog pin 10 times and average
  int adcValue = 0;
  for(int i = 0; i < 10; i++) {
    adcValue += analogRead(adcPin);
  }
  adcValue = adcValue / 10;
  float voltage = adcValue * (5.0 / 1023.0);

  // turn the ledPin on
  digitalWrite(ledPin, HIGH);

  // stop the program for <sensorValue> milliseconds:
  delay(adcValue);

  // turn the ledPin off:
  digitalWrite(ledPin, LOW);

  // stop the program for <sensorValue> milliseconds:
  delay(adcValue);

  // Clear the LCD screen before displaying new values
  lcd.clear();

  // Set the cursor to the first column of the first row
  lcd.setCursor(0, 0);
  // Print the ADC value and voltage to the LCD
  lcd.print("ADC: ");
  // Print the ADC value with a width of 4 characters, padding with spaces if necessary
  lcd.print(adcValue);
  // Print spaces to clear any leftover characters from previous readings
  lcd.print("    ");   // clear leftover chars
  // Set the cursor to the first column of the second row
  lcd.setCursor(0, 1);
  // Print the voltage value with 3 decimal places
  lcd.print("Volt: ");
  // Print the voltage value with 3 decimal places, ensuring that it takes up at least 5 characters (including the decimal point)
  lcd.print(voltage, 3);
  // Print spaces to clear any leftover characters from previous readings
  lcd.print(" V   ");  // clear leftover chars
  // Wait for 200 milliseconds before the next reading
  delay(200);
}
