#ifndef ComQueue_h
#define ComQueue_h
#include "arduino.h"
#include "ComVector.h"
class ComQueue: public ComVector
{
	private:
		uint8_t first;
		void insert(uint8_t n);
		void remove(uint8_t n);
	public:
		ComQueue():first(0)
		{}
		boolean fill();
		
		//boolean compare(ComQueue &c2);
	
		
};

#endif