int state = LOW, lastState = LOW;
void setup(){
    Serial.begin(9600);
    pinMode(13, OUTPUT);
    pinMode(2, INPUT);
    attachInterrupt(digitalPinToInterrupt(2), blink, FALLING);
}

void blink(){
  	state = !state;
}
 
void loop() {
    if (lastState != state){
		lastState = state;
        digitalWrite(13, state);
      	Serial.println(state);
    }
  	delay(0)
} 
