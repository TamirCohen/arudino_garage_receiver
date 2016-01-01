  #define N 200
  #define ZeroNum 1000
  #define RCV_PIN 3
  #define LED_PIN 13
  #define SCOPE_PIN 5
  #define DEBUG false
  #define DEMO_ARRAY_LEN 30

 
  class ComVector
  {
    public:
      boolean receive(void);
      ComVector(void);
      void clean_arr(void);
      boolean compare(ComVector &c2);
      void copy(ComVector &c2);
      int GetLength(void);
    private:
      boolean zeroes(bool state,int c_c);
      boolean Tcorrect(void);
      char read_bit(void);
      
      int _vector[N];
      int _length;
      
  };

  ComVector::ComVector(void)
  {
    _length=0;
    clean_arr();
  }
  int ComVector::GetLength()
  {
    return _length;
  }
  char ComVector::read_bit(void)
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

  boolean ComVector::zeroes(bool state,int c_c)
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
  boolean ComVector::Tcorrect(void)
  {
    int p;
    for(p=0;p<N;p++)
    {
      if(_vector[p] == 0)
      {
        return(true);
      }
      if(_vector[p]<10)
      {
        return(false);
      }
    }
  }
  boolean ComVector::compare(ComVector &c2)
  {
    int p;
    int equal=0;
    if (_length!=c2._length) return(false);
    for (p=0;p<_length;p++)
    {
      if (abs(_vector[p]-c2._vector[p])<10) equal++;
    }
    if(equal < _length)
    {return false;}
    else
    {return true;}
    
  }
  void ComVector::copy(ComVector &c2)
  {
    _length=c2._length;
    int p;
    for(p=0;p<N;p++)
    {
      _vector[p]=c2._vector[p];
    }
  }


  void ComVector::clean_arr(void)
  {
    int p;
    for(p=0;p<N;p++)
    {
    _vector[p]=0;
    }
    _length=0;
  }

  boolean ComVector::receive(void)
  {
    int j = 0;
    char c;
    bool state = 0;
    int c_nc = 0;//not correct
    int c_c = 0;
    bool mode_count = false;
    while (j<N)
    {
      c=read_bit();//read high/low - 1/0
      if(!(c==state))//if Read isnt state
      {
        c_nc++;
        if(c_nc == 5)//if 5 in a row
        {
          _vector[j] = c_c+c_nc;//write # (numbers)
          if (mode_count) //if in transmition
          {
            j++;//byte num in transmition
            if(zeroes(state,c_c))//if stopped tansmition
            {
              break;
            }
          }
          else
          {
            mode_count = zeroes(state,c_c);//check new transmition?
            if (mode_count) j++;//if in transmition count byte        
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
    _length = j;
    return(Tcorrect());
  }
  class com
  {
    private:
      ComVector _ArrVec[2]; 
    public:
      void MultiRead(void);
      ComVector* GetCode(void);
       
    
  };
  ComVector* com::GetCode()
  {return &_ArrVec[0];}
  void com::MultiRead()
  {
    char VerfStat=0;
    while(VerfStat!=1)
    {

      digitalWrite(LED_PIN,HIGH);
      digitalWrite(LED_PIN,LOW);//finish

      if(_ArrVec[VerfStat!=0].receive())
      {
        bool same=_ArrVec[0].compare(_ArrVec[1]);      
        if (same|(!VerfStat)) 
        {
          VerfStat = ((!VerfStat) ? 5 : (VerfStat-1));//if status=0->5 else status--
        }
        else//if not stat 0 or not tottaly equals
        {
          _ArrVec[0].copy(_ArrVec[1]);
          VerfStat=0;
        }
      } 
      else//if the new arr is bad
      {
        _ArrVec[VerfStat!=0].clean_arr();// clean it
      }
    _ArrVec[1].clean_arr();//clean the compare arr
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
    com m;
    m.MultiRead();
    Serial.println(m.GetCode()->GetLength());
    
    
  }
