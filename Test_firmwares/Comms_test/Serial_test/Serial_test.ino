#include <Wire.h>
int incomingByte = 0; // for incoming serial data
String readBuffer = "";


bool str_end = false;


void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  pinMode(LED_BUILTIN, OUTPUT);
  Wire.begin(); // join i2c bus (address optional for master)
  pinMode(6, OUTPUT);
  
}
byte x = 0;

void transmit(String Data){
  
  Wire.beginTransmission(4); // transmit to device #4
  char buffer[32];
  Data.toCharArray(buffer, 32);
  Wire.write(buffer);          
  Serial.println(Data);
  Wire.endTransmission();    // stop transmitting
}
void selector(){
  
  //Serial.println(readBuffer);
  if (readBuffer == "ON"){
    Serial.println("Enabled");
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(6, HIGH);
    transmit("CONNECTED");
    }
  else if (readBuffer == "FIRE"){
    Serial.println("Disabled");
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(6, LOW);
    transmit("FIRE");
    }
  else{
    transmit(readBuffer);
    }
  }
void loop() {
  // send data only when you receive data:
  while (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    if (incomingByte != 10 ){
      readBuffer += char(incomingByte);
      }
     else if (incomingByte == 10 ){
      str_end = true;
      }
  }
  if(readBuffer != "" && str_end == true){
  //Serial.println(readBuffer);
  selector();
  readBuffer = "";
  str_end = false;
  }  

}
