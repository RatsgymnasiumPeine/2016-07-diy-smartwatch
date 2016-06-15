 int displayState = 1;


// Pin configuration
#define VIBRATE_PIN1   9      // The drain pin for the vibration motor
#define BLUETOOTH_RX   11     // Receive pin for bluetooth
#define BLUETOOTH_TX   12     // Transmit pin for bluetooth
#define BLUETOOTH_KEY  6      // Key pin for bluetooth
#define POWER_PIN1     -1     // Power pin to supply additional 3,3V (-1 if not used)
#define POWER_PIN2     -1     // Power pin to supply additional 3,3V (-1 if not used)
#define BLUETOOTH_NAME "Finn Smartwatch" // The bluetooth name
#define BLUETOOTH_PIN  "1234"            // bluetooth pin

#define LOG                   // uncomment to disable serial log

void setup() {
  Serial.begin(9600);
  Log("Booting smartwatch");
  if(POWER_PIN1 != -1){
    // Turn on additional power pin 3,3V if configured
    Log("Turning on power pin 1");
    pinMode(POWER_PIN1, OUTPUT);
    digitalWrite(POWER_PIN1, HIGH);
  }else{
    Log("No power pin 1");
  }
  if(POWER_PIN2 != -1){
    // Turn on additional power pin 3,3V if configured
    Log("turning on power pin 2");
    pinMode(POWER_PIN2, OUTPUT);
    digitalWrite(POWER_PIN2, HIGH);  
  }else{
    Log("No power pin 2"); 
  }
  
  // set vibrate pin to 3,3V so it does not vibrate (only vibrates if pin is low/draining)
  Log("Setting up vibrate pin");
  pinMode(VIBRATE_PIN1, OUTPUT);
  digitalWrite(VIBRATE_PIN1, HIGH);
  
  // Setup the modules
  setupBluetooth();
  setupTouch();
  setupOLED();
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


void Log(char * message){
  #ifdef LOG
  Serial.write(message);
  #endif
}
