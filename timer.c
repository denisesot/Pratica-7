  int state = LOW, lastState = LOW;
  void setup(){
      Serial.begin(9600);
      pinMode(13, OUTPUT);
      pinMode(2, INPUT);
      
      TCCR1A - 0;
      TCCR1B = 0;
      TCNT1 = 0;
      OCR1A = 0X3D09;
      TCCR1B |= (1 << CS10) | (1 << CS12);
      TIMSK1 |= (1 << OCIE1A);
    
  }
 ISR(TIMER1_COMPA_vect){
  state = !state;
  
}
	
  void loop() {
      if (lastState != state){
          lastState = state;
          digitalWrite(13, state);
          Serial.println(state);
      }
      delay(1000);
  } 
