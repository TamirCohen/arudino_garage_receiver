/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground

 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

// These constants won't change.  They're used to give names
// to the pins used:
#define N 52 

#define startbit_low 4000
#define startbit_high 1500
#define one_logic_low 1200
#define one_logic_high 300
#define zero_logic_low 600
#define zero_logic_high 900

 // Analog output pin that the LED is attached to
char col_count=0;
bool pin_state=true;
int i=0;
int j=0;
char code[N]={1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,0,1,0,1,1,0,1,0,0,0,1,1,0,0,1,1,1,1,1,1,1,0,0,0,1,0,0,1,1,1,1,0,1,1,0,0,0};

//void (*StFuns[2]){s0,s1};
void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(3,INPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(13,OUTPUT);
}

void loop() {
  // read the analog in value:

  j=0;

  digitalWrite(13,HIGH); //LED
  
  digitalWrite(4,LOW);
  delayMicroseconds(startbit_low);
  
  digitalWrite(4,HIGH);
  delayMicroseconds(startbit_high);
  
  while (j<N) {  
    if (code[j]) {
      digitalWrite(4,LOW);
      delayMicroseconds(one_logic_low);
      digitalWrite(4,HIGH);
      delayMicroseconds(one_logic_high);
      
    } else {
      digitalWrite(4,LOW);
      delayMicroseconds(zero_logic_low);
      digitalWrite(4,HIGH);
      delayMicroseconds(zero_logic_high);      
    }
  }
  
  digitalWrite(13,LOW);  //LED
  delay(100); 
}