#define N 200
#define ZeroNum 1000
bool pin_state=true;
int i,j,k,p;
int c_nc=0;//not correct
int c_c=0;
bool state=0;
char c;//the input from transmiter
char test[20]={1,1,1,0,1,1,0,0,0,1,0,0,1,1,0,0,1,1,0,0};//ignore
int  len_ar[2][N];//the # in each state
bool state_ar[2][N];//state array
bool mode_count=false;//if transmission started
char VerfStat=0;
bool equal = true;

boolean zeroes(bool state,int c_c)
{
  if ((!state) & (c_c>ZeroNum))//state 0 and lots of 0
  {
    return true;
  }
  else
  {
    return false;
  }
}
boolean Tcorrect(int  len_ar[])
{
  for(k=0;k<N;k++)
  {
    if(len_ar[k] == 0)
    {
      return true;
    }
    
    if(len_ar[k]<10)
    {
      return false;
    }
  }
}
void setup() 
{
 
  Serial.begin(9600);//configuration
  pinMode(3,INPUT);//data from reciver
  pinMode(5,OUTPUT);//for debugging-scope
  pinMode(13,OUTPUT);//led receving
}

void loop() 
{
 
  Serial.println("start");
  while(VerfStat!=1)
  {
    j=0;
    mode_count=false;
    state = 0;
    c_c=0;
    c_nc=0;   
    digitalWrite(13,HIGH);
    
    while (j<N) 
    {  
      c=digitalRead(3);//read high/low - 1/0
      
      if(!(c==state))//if Read isnt state
      {
        c_nc++;
        if(c_nc == 5)//if 2 in a row
        {
          if (mode_count) //if in transmition
          {
             state_ar[VerfStat!=0][j] = state;//write state
             len_ar[VerfStat!=0][j] = c_c+c_nc;//write # (numbers)
             j++;
             
             if(zeroes(state,c_c))
             {
                break;
             }
           }
          else
          {
            mode_count = zeroes(state,c_c);
            //if ((!state) & (c_c>1000)) mode_count=true;//checking if #0>>1000 mode_count-true    
          }
          state=!state;//change state
          c_c=0;
          c_nc=0;      
        } 
      } 
      else 
      {
        c_c++;//add to correct
        c_c+=c_nc;//add c_nc to c_c
        c_nc=0;
      }  
    }
    digitalWrite(13,LOW);//finish
    for (i=0;i<(j-1);i++)//print for debugging 
    {
          Serial.print("state ");
          Serial.print(state_ar[VerfStat!=0][i]);
          Serial.print(" ");
          Serial.print(len_ar[0][i]);
          Serial.print(" ");
          Serial.println(len_ar[1][i]);
    }
    Serial.println( (int) Tcorrect(len_ar[VerfStat!=0]));
    Serial.print("VerfStat before:");
    Serial.println((int)VerfStat);
    
    if(Tcorrect(len_ar[VerfStat!=0]))
    {
        VerfStat = ((!VerfStat) ? 5 : (VerfStat-1));
    } else
    {
      for(p=0;p<N;p++)
      {
        len_ar[VerfStat!=0][p]=0;
      } 
    }
    Serial.print("VerfStat after:");
    Serial.println((int)VerfStat);
    
    for(p=0;p<N;p++)
    {
      len_ar[1][p]=0;
    }
   }  
  while(1);
}




/* else if ( ((len_ar[j] - (c_c+c_nc)) < -10 ) || ((len_ar[j] - (c_c+c_nc)) > 10) )//if diffrent from 1st FIX FROM HERE!!!!!
            {
              equal = false;
            }*/
