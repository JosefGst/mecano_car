#ifndef INTERRUPT_H
#define INTERRUPT_H


//Macros for digitalRead()
#define redPin9 (PINB & (1 << PB1)) >> PB1
#define redPin10 (PINB & (1 << PB2)) >> PB2


int ENC1 = 0, ENC2 = 0, ENC3 = 0, ENC4 = 0;

void init_interrupts(void){
  PCICR  |= (1 << PCIE0); //Enable Port B
  PCMSK0 |= ((1 << PB1) | (1 << PB2)); //Pin9 and Pin10
  PCICR  |= (1 << PCIE1); //Enable Port C
  PCMSK1 |= (1 << PC0); //PinA0
  PCICR  |= (1 << PCIE2); //Enable Port D
  PCMSK2 |= (1 << PD2); //Pin2
}




#endif
