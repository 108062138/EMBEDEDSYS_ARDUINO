#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
#include <stdlib.h>
LiquidCrystal_PCF8574 lcd(0x3F);
int LastVR_position = 0;
int ServoPosition = 0;
int Threshold = 140;
int buzzer = 9;
void setup() {
  Wire.begin();
  Serial.begin(19200);     // setup baud rate
  lcd.begin(16, 2);       // LCD16x2
  lcd.setBacklight(1);
  lcd.clear();
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  Serial.println("I2Cmaster begins");
}

void loop() {
  int VR_position = analogRead(A0);
  ServoPosition = map(VR_position, 0, 1023, 1, 180);
  Serial.println(ServoPosition);
  display_LCD(ServoPosition);
  if(ServoPosition > Threshold){
      tone(buzzer, 1000); // Send 1KHz sound signal...
      delay(1000);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
      delay(1000);        // ...for 1sec
  }
  delay(50);
}

void display_LCD(int ServoPosition) {
    Serial.println(ServoPosition);
    lcd.setCursor(0, 0);
    lcd.print("Position: ");
    lcd.setCursor(0, 11);
    lcd.print(ServoPosition);
    lcd.print(" ");
}
