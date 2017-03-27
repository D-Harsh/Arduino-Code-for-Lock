#include <IRremote.h>
#include <IRremoteInt.h>
#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int servoPin = 9;
Servo servo;
int angle = 0;
//check pin before starting
int RECV_PIN = 10;
int lockcode[] = {16738455, 16738455, 16738455, 16738455};
int input;
int possibleinput[10] = {16738455, 16724175, 16718055, 16743045, 16716015, 16726215, 16734885, 16728765, 16730805, 16732845};
int codelimit = 0;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  servo.attach(servoPin);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Locked");
}

void loop() {
  if (codelimit == 0) {
    if (irrecv.decode(&results)) {
      for (int i = 0; i < 10; i++) {
        if ((results.value, DEC) == possibleinput[i]) {
          break;
        } else {
          continue;
        }

      }
      {
        Serial.println(results.value, DEC);
        lcd.clear();
        lcd.print(results.value, DEC);
        input = results.value, DEC;
        irrecv.resume();
      }
      codelimit++;
      delay(100);
    }
  }
  else if (input == 16738455) {
      lcd.setCursor(0, 1);
      lcd.print("Unlocked");
      Serial.println("Unlocked");
      for (angle = 0; angle < 180; angle++)
      {
        servo.write(angle);
        delay(15);
      }
    }
    //    else {
    //      lcd.setCursor(0,1);
    //      lcd.print("Wrong passcode");
    //    }
    codelimit -= 1;
    ////    for( int i = 0; i < 1;i++){
    ////   input[i] = (char)0;
    //   }
  }



