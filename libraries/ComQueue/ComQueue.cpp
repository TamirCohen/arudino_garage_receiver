#include "ComQueue.h"
#include "arduino.h"
#define N 195
void ComQueue::insert(uint8_t n)
{
	_vector[(_length+first)%N] = n;
	if(length==N)
	{
		first++;
	}
	else
	{
		length++;
	}
}
void ComQueue::empty()
{
	_length=0;
}
boolean ComQueue::fill()
{
	
}