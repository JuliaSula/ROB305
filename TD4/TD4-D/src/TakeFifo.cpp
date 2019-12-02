#include "TakeFifo.h"
#include <iostream>
using namespace std;
TakeFifo::TakeFifo(Fifo<int> *p_fifo, Mutex *m) : fifo(p_fifo), m(m),taken(0)
{}

TakeFifo::~TakeFifo()
{}

void TakeFifo::run()
{

	bool active(true);
	while (active)
	{
		try
		{
			
			fifo->pop(1000);
			Mutex::Lock Lock(*m);
			taken++;
			
		}
		catch (const Fifo<int>::EmptyException &e)
		{
			active = false;
		}
	}
}
	
unsigned int TakeFifo::getTaken()
{
	return taken;
}
