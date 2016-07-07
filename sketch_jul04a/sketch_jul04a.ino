#include <LiquidCrystal.h>
#include <arduino.h>
LiquidCrystal lcd(12, 11, 5, 6, 4, 2);
void setup() {
  // put your setup code here, to run once:
lcd.begin(16,2);
lcd.print("hi dude");
}

void loop() {
  // put your main code here, to run repeatedly:

}
