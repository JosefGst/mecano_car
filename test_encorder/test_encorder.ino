#define ENCA 2

int pos = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ENCA, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
}

void loop() {
  Serial.println(pos);
}


void readEncoder(){
  //int b = digitalRead(ENCA);
  pos++;
}
