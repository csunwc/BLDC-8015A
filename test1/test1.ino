// BLDC-8015A driver PWM test code...
// (1) ramp up and down speed, (2) change motor direction after each ramp up/down cycle.
// setup:  Arduino Uno 
// ref: https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/
// author: C.Sun 


int pwmPin = 5;   // AVI port connects to digital pin 5, PWM 980hz
int dirPin = 7;   // F/R port connects to digital pin 7

int speed =0;    // pwm duty cycle
int direction=1; // 1 or -1 for F/R dir
int ramp = 1;  // speed ramp direction, pos or neg

void setup() {
  pinMode(dirPin,OUTPUT); // direction pin
  //Serial.begin(9600); // debug
}

void loop() {
  // speed limit check
	if (speed<0 || speed>255) {
    ramp= ramp* -1 ;// reverse 
	  speed = speed + 2*ramp; // correct overshoot
  }

  // change motor direction at stop
  if (speed==0){
    direction=direction* -1; // reverse 
    if (direction>0)
      digitalWrite(dirPin,HIGH);
    else   
      digitalWrite(dirPin,LOW);
  }

  // send PWM signal
	analogWrite(pwmPin,speed);
  //Serial.print(direction);
  //Serial.print(":");
  //Serial.println(speed);
	speed = speed + ramp;  
	delay(100); // 100 msec 
}
