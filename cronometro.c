  int state = 0;
  int hh = 0, mm = 0, ss = 0;
  int flag = 0, lastState = 0;
  void setup(){
      Serial.begin(9600);
      pinMode(13, OUTPUT);
      pinMode(2, INPUT);
      attachInterrupt(digitalPinToInterrupt(2), blink, FALLING);
      //set timer1 interrupt at 1Hz
  	  TCCR1A = 0;// set entire TCCR1A register to 0
      TCCR1B = 0;// same for TCCR1B
      TCNT1  = 0;//initialize counter value to 0
   	  // set compare match register for 1hz increments
  	  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  	  // turn on CTC mode
      TCCR1B |= (1 << WGM12);
  	  // Set CS10 and CS12 bits for 1024 prescaler
      TCCR1B |= (1 << CS12) | (1 << CS10);  
 	  // enable timer compare interrupt
	  TIMSK1 |= (1 << OCIE1A);
    
  }
 ISR(TIMER1_COMPA_vect){
  state = !state;
  
}
 void blink(){
      flag = !flag;
  }
	
  void loop() {
      if (state){
          digitalWrite(13, HIGH);
        
        if(ss < 59){
          ss = ss+1;
        }else{
          ss = 0;
          mm = mm+1;
        }
        if (mm == 60){
          mm = 0;
          hh = hh+1;
        }
        if (hh == 24){
          hh = 0;
        }
        
        Serial.println((String)""+hh+":"+mm+":"+ss);
        state = 0;
      }
	   
       if (lastState != flag){
          lastState = flag;
          digitalWrite(13, flag);
          TCNT1  = 0;
          hh = 0;
          mm = 0;
          ss = 0;
         Serial.println((String)""+hh+":"+mm+":"+ss);
      }
      delay(200);
  } 