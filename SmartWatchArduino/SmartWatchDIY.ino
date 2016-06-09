int displayState = 1;

#define VIBRATE_PIN1   A3



void setup() {
  pinMode(5, OUTPUT);
  pinMode(VIBRATE_PIN1, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(VIBRATE_PIN1, HIGH);
  digitalWrite(5, HIGH);
  
  setupBluetooth();
  setupTouch();
  setupOLED();
  
  Serial.begin(9600);
}

void loop(void) {
  loopBluetooth();
  loopTouch();
  loopOLED();
     
  if(isTouched(0)){
    displayState--;
    delay(100);
  }
  if(isTouched(11)){
    displayState++;
    delay(100);
  }
  if(displayState < 0)
    displayState = 0;
  if(displayState > 2)
    displayState = 2;
    
}
