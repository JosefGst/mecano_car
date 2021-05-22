#define ch1 A1
#define ch2 A2
#define ch3 A3
#define ch4 A4

#define ENC3 2

int16_t steering, throttle, roll, m1, m2, m3, m4; 
int pos = 0;
long prevT = 0;
float eprev = 0, eintegral = 0;


#include <AFMotor.h>
AF_DCMotor motor4(4), motor3(3), motor2(2), motor1(1);

int limit (int value);

void setup() {
  pinMode(ch1, INPUT); //works also on Digital Pins
  pinMode(ch2, INPUT);
  pinMode(ch3, INPUT);
  pinMode(ch4, INPUT);
  pinMode(ENC3, INPUT);
  
  Serial.begin(9600);
  Serial.println("Start of the meccano wheel car");
}

void loop() {
  //-----------------------------------------------------------------------------
  //read PWM ********************************************************************
  //-----------------------------------------------------------------------------

//  roll = pulseIn(ch1, HIGH);
//  throttle = pulseIn(ch2, HIGH);
//  steering = pulseIn(ch4, HIGH);
//
//  roll = map(roll, 995, 1980, -255, 255);
//  throttle = map(throttle, 995, 1988, 255, -255); //switched direction with 255, 0
//  steering = map(steering, 995, 1985, -255, 255);

//  Serial.print(roll);
//  Serial.print(" - ");
//  Serial.print(throttle);
//  Serial.print(" - ");
//  Serial.println(steering);

  m1 = (throttle + roll - steering) / 1;
  m2 = (throttle - roll - steering) / 1;
  m3 = (throttle + roll + steering) / 1;
  m4 = (throttle - roll + steering) / 1;
//  Serial.print(m1);
//  Serial.print(" \t ");
//  Serial.print(m2);
//  Serial.print(" \t ");
//  Serial.print(m3);
//  Serial.print(" \t ");
//  Serial.println(m4);

  m1 = limit(m1); m2 = limit(m2); m3 = limit(m3); m4 = limit(m4); //limit in range of -255 to +255

//  Serial.print(m1);
//  Serial.print(" \t ");
//  Serial.print(m2);
//  Serial.print(" \t ");
//  Serial.print(m3);
//  Serial.print(" \t ");
//  Serial.println(m4);

  //for testing
  m1=0; m2=0;m3=0;m4=0;

  
  float kp = 15, ki = 0, kd = 0.0;
  int target = 200;
  
//time difference
  long currT = micros();
  float deltaT = ((float)(currT-prevT))/1.0e6;
  prevT = currT;

//error
  int e = pos - target;

//derivative
  float dedt = (e-eprev)/deltaT;

//integral
  eintegral = eintegral + e*deltaT;

//control signal
  float u = kp*e + ki*eintegral + kd*dedt;

  m3 = -u;
  m3 = limit(m3);



  
  if (m1 >= 10){
    motor1.setSpeed(m1);
    motor1.run(FORWARD);
  }
  else if (m1 <= -10){
    motor1.setSpeed(abs(m1));
    motor1.run(BACKWARD);
  }
  else motor1.run(RELEASE);
//********************************************************************
  if (m2 >= 10){
    motor2.setSpeed(m2);
    motor2.run(FORWARD);
  }
  else if (m2 <= -10){
    motor2.setSpeed(abs(m2));
    motor2.run(BACKWARD);
  }
  else motor2.run(RELEASE);
  //********************************************************************
  if (m3 >= 10){
    motor3.setSpeed(m3);
    motor3.run(FORWARD);
  }
  else if (m3 <= -10){
    motor3.setSpeed(abs(m3));
    motor3.run(BACKWARD);
  }
  else motor3.run(RELEASE);
  //********************************************************************
  if (m4 >= 10){
    motor4.setSpeed(m4);
    motor4.run(FORWARD);
  }
  else if (m4 <= -10){
    motor4.setSpeed(abs(m4));
    motor4.run(BACKWARD);
  }
  else motor4.run(RELEASE);

  //read Encoder
  attachInterrupt(digitalPinToInterrupt(ENC3),readEncoder,RISING);


  eprev = e;
  Serial.print(target);
  Serial.print(" ");
  Serial.println(pos);
}





// Private Functions*******************************************************************
int limit (int value){ //limits value in range of -255 to +255
  if (value >= 255) return 255;
  else if (value <= -255) return -255;
  else return value;  
}

void readEncoder(){
  if (m3 > 0) pos++;
  else pos--; 
  //Serial.println(pos);
}
