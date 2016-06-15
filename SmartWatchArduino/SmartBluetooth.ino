#include <SoftwareSerial.h>
#include "Time.h"
#include "SerialCommand.h"
SoftwareSerial bluetooth(BLUETOOTH_RX, BLUETOOTH_TX); // RX, TX
SerialCommand bluetoothCommand(bluetooth);   // The demo SerialCommand object


String messageTxt;
long updateTimeTimer = -1000L*60;
void setupBluetooth(){
   /*
     Setup bluetooth module
   */
   Log("Setting up bluetooth module");
   pinMode(BLUETOOTH_KEY, OUTPUT);                   // key pin
   digitalWrite(BLUETOOTH_KEY, HIGH);                // Pull key pin high to enable AT commands
   bluetooth.begin(9600);                 // Start serial communication channel with bluetooth module
   String atCommand = String("AT+NAME=\""); // AT command generation
   atCommand.concat(BLUETOOTH_NAME);
   atCommand.concat("\"\r\n");
   bluetooth.write(atCommand.c_str());    // Set the name of the bluetooth device
   bluetooth.write("AT+PSWD=");
   bluetooth.write(BLUETOOTH_PIN);
   bluetooth.write("\r\n");   // password of the bluetooth device
   bluetooth.write("AT+IPSCAN=1024,1,1024,1\r\n"); // maximum power saving
   bluetooth.write("AT+ADDR?\r\n");
   delay(200);
   while (bluetooth.available())
     Serial.write(bluetooth.read());
   digitalWrite(BLUETOOTH_KEY, LOW);                 // pull key pin to low to disable AT commands an enable normal data flow
   
   // clear serial buffer
   delay(200);
   while (bluetooth.available())
     bluetooth.read();
     
   
   
   bluetoothCommand.addCommand("T", setTime);
   bluetoothCommand.addCommand("V", vibrate);
   bluetoothCommand.addCommand("M", messageStart);
   bluetoothCommand.addCommand("C", message);
}

void loopBluetooth(){
  bluetoothCommand.readSerial();
  
  /*if(updateTimeTimer < millis()-1000L*10){
    bluetooth.write("REQUESTTIME\r\n"); 
    updateTimeTimer = millis();
  }*/
}

void setTime(){
 long time = atol(bluetoothCommand.next());
 setTime(time); 
 Serial.println("Got TIMESET");
 Serial.println(time);
}

void vibrate(){
  Serial.println("Got VIBRATE");
  for(int i = 0; i < 4; i++){
    digitalWrite(VIBRATE_PIN1, LOW);
    delay(200);
    digitalWrite(VIBRATE_PIN1, HIGH);
    delay(75);
  }
}
void messageStart(){
  Serial.println("Got MESSAGESTART");
  messageTxt = "";
}
void message(){
  Serial.println("Got MESSAGE");
  while(true){
    String messageBuffer = bluetoothCommand.next();
    if(messageBuffer != NULL){
      Serial.println(messageBuffer);
      messageTxt += messageBuffer + " ";
    }else{
      break;
    }
  }
  Serial.println(messageTxt);
}
