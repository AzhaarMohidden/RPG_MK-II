#include <Wire.h>
#include <IRremote.h>

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;


unsigned long connection_code = 1389560526;//input raw code here
//unsigned long connection_code = 4060939260;
int fire_bit_length = 46;
// int fire_bit_length = 32;
int counter = 0;
int count_enable = 0;


void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

byte x = 0;

void loop()
{
 if (irrecv.decode(&results)) {
    counter = counter+1;
    Serial.println(results.value, DEC);
    dump(&results);
    irrecv.resume(); // Receive the next value
  }
  //testt("Hellow");
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
    //Connected_status = true;
    transmit("CONNECTED");
    count_enable = count;

    }
    else {
      transmit(String(results->value));
      }

    if(count== fire_bit_length && counter != count_enable){
    transmit("FIRE");
   
    
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


void transmit(String Data){
  
  Wire.beginTransmission(4); // transmit to device #4
  char buffer[32];
  Data.toCharArray(buffer, 32);
  Wire.write(buffer);          
  Serial.println(Data);
  Wire.endTransmission();    // stop transmitting

  

  //x++;
  /*delay(500);
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write("OFF");        // sends five bytes              // sends one byte  
  Wire.endTransmission();    // stop transmitting
  delay(500);*/
  }
