int ENC1 = 0, ENC2 = 0, ENC3 = 0, ENC4 = 0;



void setup() {
  PCICR  |= (1 << PCIE0); //Enable Port B
  PCMSK0 |= ((1 << PB1) | (1 << PB2)); //Pin9 and Pin10
  PCICR  |= (1 << PCIE1); //Enable Port C
  PCMSK1 |= (1 << PC0); //PinA0
  PCICR  |= (1 << PCIE2); //Enable Port D
  PCMSK2 |= (1 << PD2); //Pin2
  
  

  Serial.begin(9600);
}

void loop() {
  
  Serial.println((String)"ENC1: " + ENC1 + "\t ENC2: " + ENC2 + "\tENC3: " + ENC3 + "\t ENC4: " + ENC4);
  delay(1000);
}

//ISR for port B
ISR (PCINT0_vect){ //since pin 9 and 10 are both at port B, check which one changed
  static bool prev1 = digitalRead(10), prev4 = digitalRead(9);
  if (digitalRead(9) != prev4){ //check for falling or rising 
    ENC4++;
    prev4 = digitalRead(9);
  }
  else if (digitalRead(10) != prev1){ //check for falling or rising 
    ENC1++;
    prev1 = digitalRead(10);
  }
}

//ISR for port C
ISR (PCINT1_vect){ //Pin A0
  ENC3++;
}

//ISR for port D
ISR (PCINT2_vect){ //Pin 2
  ENC2++;
}
