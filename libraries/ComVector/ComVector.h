#ifndef ComVector_h
#define ComVector_h

#define N 195
#include "Arduino.h" 
class ComVector
{
    public:
      boolean receive(void);
      ComVector(void);
	  ComVector(int n);
	  ComVector(int n,String Name);
      void clean_arr(void);
      boolean compare(ComVector &c2);
      void copy(ComVector &c2);
      int GetLength(void);
	  void writeEE();
	  void readEE(char idx);
	  void printVec(void);
	  void transmit(void);
	  void setName(String Name);
	  String GetName();
    private:
      boolean zeroes(bool state,int c_c);
      boolean Tcorrect(void);
      char read_bit(void);
	  String name;
      int _vector[N];//stATIC
      int _length;
      
};
#endif