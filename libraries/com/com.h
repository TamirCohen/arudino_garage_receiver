#ifndef com_h
#define com_h
#include "Arduino.h" 
#include "ComVector.h"
class com
  {
    private:
      ComVector _ArrVec[2]; 
    public:
      void MultiRead(void);
      ComVector* GetVec(void);
	  void clean(void);
	  void transmit(uint8_t loc);
       
    
  };
#endif