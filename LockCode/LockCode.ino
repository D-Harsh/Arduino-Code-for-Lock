#include <LiquidCrystal.h>
const int SW_pin = 2;
const int X_pin = 0;
const int Y_pin = 1;
int counter = 0;
int limit = 0;
char *input[4]; 
char *passcode[4] = {"Right","Right","Right","Right"};
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  lcd.print("Locked");
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
}

void loop() {
  if (counter < 4) {
    if (analogRead(X_pin) > 1000) {
      lcd.setCursor(0,1);
      lcd.print("Down");
      *input[counter] = "Down";
      counter++;
    }
    if (analogRead(X_pin) < 20) {
      lcd.setCursor(0,1);
      lcd.print("Up");
      *input[counter] = "Up";
      counter++;
    }
    if (analogRead(Y_pin) > 1000) {
      lcd.setCursor(0,1);
      lcd.print("Left");
      *input[counter] = "Left";
      counter++;
    }
    if (analogRead(Y_pin) < 20) {
      lcd.setCursor(0,1);
      lcd.print("Right");
      *input[counter] = "Right";
      counter++;
    }
    delay(500);
  }
  else {
      if ((*input[0]+*input[1]+*input[2]+*input[3]) == (*passcode[0]+*passcode[1]+*passcode[2]+*passcode[3])){
          lcd.clear();
          lcd.print("Accessing Matrix");
      else if (limit < 3){
        lcd.setCursor(0,1);
        limit++;
        lcd.print("Wrong Attempt #"+limit);
      }
  }
}
}



