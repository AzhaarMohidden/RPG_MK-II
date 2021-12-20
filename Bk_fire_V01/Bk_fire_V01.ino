/*RPG-7 Back Fire Unit Controller
 * Firmware v*
 * A0 - Read Connection satatus of pyro
 * D6 - TIP120 NPN Relay enable
 * D2 - input for IR reader
 * 
 * Author: Azhaar Mohideen
 * 
 
 */
#include <IRremote.h>

bool Connected_status = false;
bool fire_code_recieved = false;
bool Loaded = false;

unsigned long connection_code = 1389560526;//input raw code here
int fire_bit_length = 46;
int counter = 0;
int count_enable = 0;


int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);

}

void loop() {
  //Raise();
  //test();
  if (irrecv.decode(&results)) {
    counter = counter+1;
    Serial.println(results.value, DEC);
    dump(&results);
    digitalWrite(9, HIGH);
    delay(100);
    digitalWrite(9, LOW);
    irrecv.resume(); // Receive the next value
  }
  int p_st = analogRead(A0);
  if(p_st >=50 && Loaded == false){
    digitalWrite(9, HIGH);
    delay(200);
    digitalWrite(9, LOW);
    delay(200);
    Loaded = true;
    }
  else if(p_st < 2 && Loaded == true){
    Loaded = false;
    }
    

}
void test(){
  delay(100);
  FIRE();
  delay(5000);
  }
void FIRE(){
  digitalWrite(6, HIGH);
  delay(2000);
  digitalWrite(6, LOW);
  delay(2000);
  }

void Raise(){
 /* for(int i = 150; i>=0; i = i - 10){
  digitalWrite(9, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(i+10);                       // wait for a second
  digitalWrite(9, LOW);    // turn the LED off by making the voltage LOW
  delay(i);    
    }  */

   for(int i=2; i>=0; i=i-1){
    digitalWrite(9, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(50);                       // wait for a second
    digitalWrite(9, LOW);    // turn the LED off by making the voltage LOW
    delay(50);  
    }
  
  }

void dump(decode_results *results) {
  // Dumps out the decode_results structure.
  // Call this after IRrecv::decode()
  int count = results->rawlen;
  Serial.print(results->value, HEX);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print(count);
  Serial.print("): ");

  if(results->value == connection_code){
    Serial.print("Successfull enabled");
    Connected_status = true;
    digitalWrite(9, HIGH);
    delay(200);
    digitalWrite(9, LOW);
    delay(200);
    if(Loaded == true){
      Raise();
      }
    
    count_enable = count;
    }
    if((Connected_status == true) && count== fire_bit_length && counter != count_enable){
    digitalWrite(6, HIGH);
    Serial.print("Successfull activated");
    delay(2000);
    digitalWrite(6, LOW);
    Connected_status = false;
    }
  
//  for (int i = 1; i < count; i++) {
//    if (i & 1) {
//      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
//    }
//    else {
//      Serial.write('-');
//      Serial.print((unsigned long) results->rawbuf[i]*USECPERTICK, DEC);
//    }
//    Serial.print(" ");
//  }
  Serial.println();
}
