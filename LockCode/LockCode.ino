#include <LiquidCrystal.h> //Library for LCD Display
#include <Servo.h> //Library for controlling Servo
int servoPin = 9; // Digital input pin for servo
Servo servo; // Declaring the servo
int angle = 0; // servo position in degrees
const int SW_pin = 13; //Digital input pin for joystick switch
const int X_pin = 0; //Analog input pin for X axis of the joystick
const int Y_pin = 1; //Analog input pin for Y axis of the joystick
int counter = 0; //counts the number of components per input
int limit = 0; //counts the number of input
char *input[4]; //stores components of inputs
char *passcode[4] = {"Right", "Right", "Right", "Right"}; //password for locking and unlocking the lock
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Digital input pins connected to LCD Display

void setup() {
  servo.attach(servoPin); //attaches the servo pin to the servo
  lcd.begin(16, 2);//declares the rows and colums of the LCD Screen (2 rows, 16 columns)
  lcd.print("Locked");//Prints Locked in the beginning
  pinMode(SW_pin, INPUT); //sets up the joystick switch in order to take in input
  digitalWrite(SW_pin, HIGH);
}

void loop() {
  if (limit < 3) {
    //checks if user still has attempts left for input
    if (counter < 4) {
      //checks if user has finished inputing a valid password
      if (analogRead(X_pin) > 1000) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Down");
        lcd.setCursor(0, 1);
        lcd.print(counter + 1);
        input[counter] = "Down";
        counter++;
      }
      else if (analogRead(X_pin) < 60) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Up");
        lcd.setCursor(0, 1);
        lcd.print(counter + 1);
        input[counter] = "Up";
        counter++;
      }
      else if (analogRead(Y_pin) > 1000) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Left");
        lcd.setCursor(0, 1);
        lcd.print(counter + 1);
        input[counter] = "Left";
        counter++;
      }
      else if (analogRead(Y_pin) < 60) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Right");
        lcd.setCursor(0, 1);
        lcd.print(counter + 1);
        input[counter] = "Right";
        counter++;
      }
      /*Reads the axis of the joystick and saves the input in a pointer.
       * Also displays the input and the digit number of the input on the lcd module
       */
      delay(200);
    }
    else {
      if ((input[0] == passcode[0]) && (input[1] == passcode[1]) && (input[2] == passcode[2]) && (input[3] == passcode[3])) {
        lcd.clear();
        limit = 0;
        counter = 0;
        if (angle == 0) {
          lcd.print("Unlocked");
          for (angle = 0; angle < 90; angle++)
          {
            servo.write(angle);
            delay(15);
          }
        }
        else {
          lcd.print("Locked");
          for (angle = 90; angle > 0; angle--)
          {
            servo.write(angle);
            delay(15);
          }
        }
      }
      else {
        lcd.clear();
        limit++;
        counter -= 4;
        lcd.print("Wrong Attempt");
        lcd.setCursor(0, 1);
        lcd.print("Attempts left:");
        lcd.setCursor(15, 1);
        lcd.print(3-limit);
      }
    }
    /*
     * Compares the user's input to the set password. If the input is correct it locks or unlocks accordingly
     * If the input is incorrect, it notifies the user about their wrong attempt and the amount of attempts left
     */
  }
  else {
    lcd.clear();
    lcd.print("Intruder Alert");
    lcd.setCursor(0, 1);
    lcd.print("Locked");
    delay(500);
    if (angle == 90) {
      for (angle = 90; angle > 0; angle--)
      {
        servo.write(angle);
        delay(15);
      }
    }
  }
  /*
   * If user has exhausted the amount of attempts available, the device locks itself and 
   * the display alerts the user that it has detected an intruder. 
   */
}



