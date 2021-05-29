#include "my_functions.h"
#include "Interrupt.h"

#define ch1 A1
#define ch2 A2
#define ch3 A3
#define ch4 A4
#define MINLIM 30


//radio
int16_t steering, throttle, roll, m1, m2, m3, m4; 
//rotary encoder


#include <AFMotor.h>
AF_DCMotor motor4(4), motor3(3), motor2(2), motor1(1);



void setup() {
  pinMode(ch1, INPUT); //works also on Digital Pins
  pinMode(ch2, INPUT);
  pinMode(ch3, INPUT);
  pinMode(ch4, INPUT);

  init_interrupts();

  
  
  Serial.begin(9600);
  Serial.println("Start of the meccano wheel car");
}

void loop() {
  //-----------------------------------------------------------------------------
  //read PWM ********************************************************************
  //-----------------------------------------------------------------------------

  roll = pulseIn(ch1, HIGH);
  throttle = pulseIn(ch2, HIGH);
  steering = pulseIn(ch4, HIGH);

  roll = map(roll, 995, 1980, -255, 255);
  throttle = map(throttle, 995, 1988, 255, -255); //switched direction with 255, 0
  steering = map(steering, 995, 1985, -255, 255);

  m1 = (throttle + roll - steering) / 1;
  m2 = (throttle - roll - steering) / 1;
  m3 = (throttle + roll + steering) / 1;
  m4 = (throttle - roll + steering) / 1;

  m1 = limit(m1); m2 = limit(m2); m3 = limit(m3); m4 = limit(m4); //limit in range of -255 to +255

  
  if (m1 >= MINLIM){
    motor1.setSpeed(m1);
    motor1.run(FORWARD);
  }
  else if (m1 <= -MINLIM){
    motor1.setSpeed(abs(m1));
    motor1.run(BACKWARD);
  }
  else motor1.run(RELEASE);
//********************************************************************
  if (m2 >= MINLIM){
    motor2.setSpeed(m2);
    motor2.run(FORWARD);
  }
  else if (m2 <= -MINLIM){
    motor2.setSpeed(abs(m2));
    motor2.run(BACKWARD);
  }
  else motor2.run(RELEASE);
  //********************************************************************
  if (m3 >= MINLIM){
    motor3.setSpeed(m3);
    motor3.run(FORWARD);
  }
  else if (m3 <= -MINLIM){
    motor3.setSpeed(abs(m3));
    motor3.run(BACKWARD);
  }
  else motor3.run(RELEASE);
  //********************************************************************
  if (m4 >= MINLIM){
    motor4.setSpeed(m4);
    motor4.run(FORWARD);
  }
  else if (m4 <= -MINLIM){
    motor4.setSpeed(abs(m4));
    motor4.run(BACKWARD);
  }
  else motor4.run(RELEASE);

  

  Serial.println((String)"ENC1: " + ENC1 + "\t ENC2: " + ENC2 + "\tENC3: " + ENC3 + "\t ENC4: " + ENC4);


}


// Private Functions*******************************************************************

//ISR for port B
ISR (PCINT0_vect){ //since pin 9 and 10 are both at port B, check which one changed
  static bool prev1 = digitalRead(10), prev4 = digitalRead(9);
  if (digitalRead(9) != prev4){ //check for falling or rising 
    if (m4 > 0) ENC4++;   //check wether forward or backward rotation
    else ENC4--;
    prev4 = digitalRead(9);
  }
  else if (digitalRead(10) != prev1){ //check for falling or rising 
    if (m1 > 0) ENC1++;
    else ENC1--;
    prev1 = digitalRead(10);
  }
}

//ISR for port C
ISR (PCINT1_vect){ //Pin A0
  if (m3 > 0) ENC3++;
  else ENC3--; 
}

//ISR for port D
ISR (PCINT2_vect){ //Pin 2
  if (m2 > 0) ENC2++;
  else ENC2--;
}
