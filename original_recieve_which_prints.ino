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
#define N 400 
 // Analog output pin that the LED is attached to
char col_count=0;
bool pin_state=true;
int i=0;
int j=0;
int c_nc=0;
int c_c=0;
bool state=0;
char c;
char test[20]={1,1,1,0,1,1,0,0,0,1,0,0,1,1,0,0,1,1,0,0};
int  len_ar[N];
bool state_ar[N];
bool mode_count=false;


void setup() {
 
  Serial.begin(9600);
  pinMode(3,INPUT);
  pinMode(5,OUTPUT);
  pinMode(13,OUTPUT);
}

void loop() {
 
  Serial.println("start");

  i=0;j=0;
 
   digitalWrite(13,HIGH);
  while (j<N) {  
    c=digitalRead(3);
    
    if(!(c==state))
    {
      c_nc++;
      if(c_nc==2)
      {
        if (mode_count) {
          state_ar[j]=state;
          len_ar[j]=c_c+c_nc;
          j++;
        }
        else
        {
          if ((!state) & (c_c>1000)) mode_count=true;    
        }
        state=!state;
        c_c=0;
        c_nc=0;      
      } 
    } 
    else 
    {
      c_c++;
      c_c+=c_nc;
      c_nc=0;
    }  
  }
  digitalWrite(13,LOW);
  for (i=0;i<N;i++) {
        Serial.print("state ");
        Serial.print(state_ar[i]);
        Serial.print(" ");
        Serial.println(len_ar[i]);
  }

  while(1);
}