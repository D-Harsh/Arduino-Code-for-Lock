const int VRxPin= 0; //VRx pin connected to arduino pin A0
const int VRyPin= 1; //VRy pin connected to arduino in A1
const int SwButtonPin= 13; //SW pin connected to arduino pin D13

int pressed= -1; //this variable will determine whether joystick has been pressed down (selected)
int x= -1;//this variable will hold the X-coordinate value
int y= -1; //this variable will hold the Y-coordinate value

void readJoystick() {
pressed= digitalRead(SwButtonPin);//reads whether joystick has been pressed down (selected) or not
x= analogRead(VRxPin);//reads the X-coordinate value
y= analogRead(VRyPin);//reads the Y-coordinate value
}

void setup() {
pinMode(SwButtonPin, INPUT);//sets the SW switch as input
digitalWrite(SwButtonPin, HIGH);//sets the SW button HIGH
Serial.begin(9600);//sets the baud rate
}

void loop() {
readJoystick();//calls this function which reads the digital input button SW, the X-coordinate and the Y-coordinate
Serial.print("X: ");
Serial.println(x);//prints the X-coordinate
Serial.print("Y: ");
Serial.println(y);//prints the Y-coordinate
Serial.print (" Pressed: ");
Serial.println(pressed);//prints whether joystick knob has been pressed or not
delay(10);
}
