// These constants won't change.  They're used to give names
// to the pins used:
#define N 52 

#define startbit_low 4000
#define startbit_high 1500
#define one_logic_low 600
#define one_logic_high 170
#define zero_logic_low 300
#define zero_logic_high 450

 // Analog output pin that the LED is attached to
char col_count=0;
bool pin_state=true;
int i=0;
int j=0;
char code[N]={1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,0,1,0,1,1,0,1,0,0,0,1,1,0,0,1,1,1,1,1,1,1,0,0,0,1,0,0,1,1,1,1,0,1,1,0,0,0};

void setup() {
  pinMode(5,OUTPUT);
  pinMode(13,OUTPUT);
}

void loop() {
  // read the analog in value:

  j=0;

  digitalWrite(13,HIGH); //LED
  
  digitalWrite(5,LOW);
  delayMicroseconds(startbit_low);
  
  digitalWrite(5,HIGH);
  delayMicroseconds(startbit_high);
  
  while (j<N) {
    if (code[j]) {
      digitalWrite(5,LOW);
      delayMicroseconds(one_logic_low);
      digitalWrite(5,HIGH);
      delayMicroseconds(one_logic_high);
      
    }
    else 
    {
      digitalWrite(5,LOW);
      delayMicroseconds(zero_logic_low);
      digitalWrite(5,HIGH);
      delayMicroseconds(zero_logic_high);      
    }
    j++;
  }
  digitalWrite(5,LOW);
  digitalWrite(13,LOW);  //LED
  delay(100); 
}
