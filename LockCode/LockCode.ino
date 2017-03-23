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
char lockCode[4];
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

void loop() 
  {
  if (irrecv.decode(&results))
    {
     Serial.println(results.value, HEX);
     irrecv.resume(); // Receive the next value
     delay(2000);
   }
   if (angle == 0){
    servo.write(90);
    angle+=90;
   }
   if (angle == 90){
    servo.write(0);
    angle-=90;
   }
   if (angle == 90){
    lcd.print("Unlocked");
   }
   else{
    lcd.print("Locked");
   }
}
