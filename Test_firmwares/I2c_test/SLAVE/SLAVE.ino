
// Relay status input pin A2
#include <Wire.h>

bool LOADED = false;
bool CONNECTED_STATUS = false;
bool FIRE_CODE_RECIEVED = false;
bool RELAY_FAULTY=false;


String rec = "";

int relay_trigger = 6;

int dev_status_led = 4;
int pyro_status_led = 5;
int IR_status_led = 8;


void setup()
{
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  //pinMode(LED_BUILTIN, OUTPUT);
  pinMode(dev_status_led, OUTPUT);
  pinMode(pyro_status_led, OUTPUT);
  pinMode(IR_status_led, OUTPUT);
}

void loop()
{
  REC_status();
  DEV_status();
  LED();
  
  
  
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void FUNCTION(){
  if((FIRE_CODE_RECIEVED == true) && (CONNECTED_STATUS == true) && (LOADED == true) )
  {
    FIRE();
    }
  }
void FIRE(){
  digitalWrite(relay_trigger, HIGH);
  delay(2000);
  digitalWrite(relay_trigger, LOW);
  LOADED = false;
  CONNECTED_STATUS = false;
  FIRE_CODE_RECIEVED = false;
  RELAY_FAULTY = false;
  delay(2000);
  
  }
void LED(){
   if(LOADED == true){
    led_out(pyro_status_led, 1, 50, true, false);
    }
   else{
    led_out(pyro_status_led, 3, 50, false, false);
    }
    
   if(CONNECTED_STATUS == true){
    led_out(dev_status_led, 1, 50, true, false);
    //digitalWrite(dev_status_led, HIGH);
    Serial.println("CONNECTED_STATUS: TRUE");
    }
   else if(CONNECTED_STATUS == false){
    digitalWrite(dev_status_led, LOW);
    }

   if(RELAY_FAULTY== true){
    led_out(dev_status_led, 10, 200, false, true);
    }
  }
void DEV_status(){
  int PYRO_LOADED = analogRead(A0);
  int RELAY_STATUS = analogRead(A2);
  
  if(PYRO_LOADED >=300){
    LOADED = true;
    }
  else{
    LOADED = false;
    }
     
  if (RELAY_STATUS >= 300){
    RELAY_FAULTY = true;
    }
  else {
    RELAY_FAULTY = false;
    }
  }
void REC_status(){
  //delay(10);
  
  //Serial.print("Rec: ");
  //Serial.println(rec);
  if (rec == "CONNECTED"){
    //digitalWrite(LED_BUILTIN, HIGH);
    CONNECTED_STATUS = true;
    Serial.print("Rec: ");
    Serial.println(rec);
    }
  if (rec == "FIRE"){
    //digitalWrite(LED_BUILTIN, LOW);
    FIRE_CODE_RECIEVED = true;
    Serial.print("Rec: ");
    Serial.println(rec);
    FUNCTION();
    }
  rec = "";
  }
void receiveEvent(int howMany)
{
  while(0 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    //Serial.print(c);         // print the character
    rec += char(c);
  }
  
  //Serial.println(rec);
  led_out(IR_status_led, 2, 50, false, true);
  
}

void led_out(int led, int times, int interval, bool stay_on, bool blinks){
  if(blinks == true){
    for (int i = times; i>=0; i = i-1){
    digitalWrite(led, HIGH);
    delay(interval);
    digitalWrite(led, LOW);
    delay(interval);
    }
    }
    else if(stay_on == true && blinks == false){
      digitalWrite(led, HIGH);
      }
    else if(stay_on == false && blinks == false){
      digitalWrite(led, LOW);
      }
    
  }
