#ifndef ComVector_h
#define ComVector_h

#define N 200
#include "Arduino.h" 
 class ComVector
  {
    public:
      boolean receive(void);
      ComVector(void);
	  ComVector(int n);
      void clean_arr(void);
      boolean compare(ComVector &c2);
      void copy(ComVector &c2);
      int GetLength(void);
	  void writeEE(char idx);
	  void readEE(char idx);
	  void printVec(void);
    private:
      boolean zeroes(bool state,int c_c);
      boolean Tcorrect(void);
      char read_bit(void);
      
      int _vector[N];
      int _length;
      
  };
#endif