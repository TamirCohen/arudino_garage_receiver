#ifndef com_h
#define com_h
#include "Arduino.h" 
#include "ComVector.h"
#include "ComQueue.h"
class com
  {
    private:
      ComQueue _ArrVec[2]; 
	  bool interupt;
    public:
      void MultiRead(uint8_t n);
      ComVector* GetVec(void);
	  void clean(void);
	  void transmit(uint8_t loc);
	  void Cinterupt(void);
	  boolean status(void);
       
    
  };
#endif