#ifndef ComVector_h
#define ComVector_h

#define N 200
#include "Arduino.h" 
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
#endif