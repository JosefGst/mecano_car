void setup() {
  Serial.begin(9600);
}

void loop() {
  
  for (float i = 0; i<360; i++){
    static float y = 0.0;
    y = sin(i * DEG_TO_RAD)*250;
    Serial.println(y);
  }

}
