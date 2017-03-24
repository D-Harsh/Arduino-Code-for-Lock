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
int lockcode[] = {1,2,3,4};
int input[4];
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
if (codelimit != 4){
 if (irrecv.decode(&results))
    {
     Serial.println(results.value, DEC);
     lcd.clear();
     lcd.print(results.value, DEC);
     input[codelimit] = (results.value, DEC);
     irrecv.resume();
    }
    codelimit++;
    delay(2000);
    }
   else{
    if (input == lockcode){
      for(angle = 0; angle < 180; angle++)  
  {                                  
    servo.write(angle);               
    delay(15);                   
  } 
      lcd.clear();
      lcd.print("Unlocked");
    }
    else {
      lcd.setCursor(0,1);
      lcd.print("Wrong passcode");
    }
    codelimit -= 4;
    for( int i = 0; i < sizeof(input);i++)
   input[i] = (char)0;
   }
}


