#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int moisturePin = A0;
const int relayPin = 2;

void setup() {
  Serial.begin(9600);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); 

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("IRRIGATION");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM STARTING");
  delay(3000);
  lcd.clear();
}

void loop() {

  int value = analogRead(moisturePin);

  Serial.print("Moisture value: ");
  Serial.println(value);

  lcd.setCursor(0, 0);
  lcd.print("                ");  

  lcd.setCursor(0, 0);

  if (value > 950) {
    digitalWrite(relayPin, LOW);  
    lcd.print("Pump: ON ");
  } else {
    digitalWrite(relayPin, HIGH); 
    lcd.print("Pump: OFF");
  }

  lcd.setCursor(0, 1);

  if (value < 300) {
    lcd.print("Moisture: HIGH ");
  } else if (value >= 300 && value <= 950) {
    lcd.print("Moisture: MID  ");
  } else {
    lcd.print("Moisture: LOW  ");
  }

  delay(500);
}