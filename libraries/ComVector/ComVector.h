#ifndef ComVector_h
#define ComVector_h

#define N 190
#include "Arduino.h" 
class ComVector
{
    public:
      boolean receive(void);
      ComVector(void);
	  ComVector(int n);
	  ComVector(int n,String Name);
      void clean_arr(void);
      void copy(ComVector &c2);
      int GetLength(void);
	  void writeEE();
	  void readEE(char idx);
	  virtual void printVec(void);
	  void transmit(void);
	  void setName(String Name);
	  String GetName();
	  virtual boolean compare(ComVector &c2);
	protected:
		uint8_t _vector[N];//stATIC
		char read_bit(void);
		uint8_t _length;
	  
    private:
      boolean zeroes(bool state,int c_c);
      boolean Tcorrect(void);
	  String name;
      
};
#endif