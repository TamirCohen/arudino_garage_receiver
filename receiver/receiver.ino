#define N 200
#define ZeroNum 1000
#define RCV_PIN 3
#define LED_PIN 13
#define SCOPE_PIN 5
#define DEBUG false
#define DEMO_ARRAY_LEN 30

int i,j,k,p;
int c_nc=0;//not correct
int c_c=0;
bool state=0;
char c;//the input from transmiter
char test[20]={1,1,1,0,1,1,0,0,0,1,0,0,1,1,0,0,1,1,0,0};//ignore
int len_ar[2][N];//the # in each state
bool state_ar[2][N];//state array
bool mode_count=false;//if transmission started
char VerfStat=0;
int equal;

char read_bit(void)
{
	static int demo[DEMO_ARRAY_LEN]={1500,70,30,70,30,70,30,70,30,70,1500,10,1500,70,30,70,30,70,30,70,30,70,1500,10,1500,40,50,40,1500,10};
	static char idx=0;
	static int idx_internal=demo[0];
	static bool state=false;
	
	if (!DEBUG) 
		return(digitalRead(RCV_PIN));
	else 
	{
		if (idx_internal==0)
		{
			idx++;
			idx=idx % DEMO_ARRAY_LEN;
			idx_internal=demo[idx];
			state=!state;
 		}
		else
			idx_internal--;
		return(state);
	}
}

boolean zeroes(bool state,int c_c)
{
	if ((!state) & (c_c>ZeroNum))//state 0 and lots of 0
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
boolean Tcorrect(int  len_ar[])
{
	for(k=0;k<N;k++)
	{
		if(len_ar[k] == 0)
		{
			return(true);
		}
		if(len_ar[k]<10)
		{
			return false;
		}
	}
}
void clean_arr(int* array)
{
  int p;
  for(p=0;p<N;p++)
  {
    array[p]=0;
  }
}
void setup()
{
	Serial.begin(9600);//configuration
	pinMode(RCV_PIN,INPUT);//data from reciver
	pinMode(SCOPE_PIN,OUTPUT);//for debugging-scope
	pinMode(LED_PIN,OUTPUT);//led receving
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
		digitalWrite(LED_PIN,HIGH);

		while (j<N)
		{
			c=read_bit();//read high/low - 1/0

			if(!(c==state))//if Read isnt state
			{
				c_nc++;
				if(c_nc == 5)//if 5 in a row
				{
                                        state_ar[VerfStat!=0][j] = state;//write state
					len_ar[VerfStat!=0][j] = c_c+c_nc;//write # (numbers)
					if (mode_count) //if in transmition
					{
						j++;
						if(zeroes(state,c_c))
						{
							break;
						}
					}
					else
					{
						mode_count = zeroes(state,c_c);
                                                if (mode_count) j++;        
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
		digitalWrite(LED_PIN,LOW);//finish

		if(Tcorrect(len_ar[VerfStat!=0]))
		{
                        Serial.print("VerfStat before:");
		        Serial.println((int)VerfStat);
                        equal=0;
                        for (p=0;p<j;p++)
                          if (abs(len_ar[1][p]-len_ar[0][p])<10) equal++;
                        Serial.print("Equals:");
                        Serial.print(equal);  
                        Serial.print(" ");
                        Serial.print(j-equal);
                        Serial.print(" ");
                        Serial.println(j);
			if ((equal==j)|(!VerfStat)) 
                        {
                                  VerfStat = ((!VerfStat) ? 5 : (VerfStat-1));
/*                                  for (i=0;i<j;i++)//print for debugging
		                  {
                                        Serial.print(i);
                			Serial.print(" state ");
                			Serial.print(state_ar[VerfStat!=0][i]);
                			Serial.print(" ");
                			Serial.print(len_ar[0][i]);
                			Serial.print(" ");
                			Serial.println(len_ar[1][i]);
                                  }     */
                                  Serial.print("VerfStat after:");
		                  Serial.println((int)VerfStat);
                        }
                        
                        else
                        {
                          clean_arr(len_ar[1]);
                          for (p=0;p<j;p++)
                          {
                            len_ar[0][p]=len_ar[1][p];
                          }
                          VerfStat=0;
                        }
		} else
		{
		  clean_arr(len_ar[VerfStat!=0]);
		}
                clean_arr(len_ar[1]);
	}
	while(1);
}
