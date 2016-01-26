#ifndef com_h
#define com_h
#include "Arduino.h" 
class com
  {
    private:
      ComVector _ArrVec[2]; 
    public:
      void MultiRead(void);
      ComVector* GetVec(void);
       
    
  };
#endif