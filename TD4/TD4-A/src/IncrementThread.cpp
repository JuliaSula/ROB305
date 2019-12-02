#include "IncrementThread.h"
#include <iostream>
using namespace std;
IncrementThread::IncrementThread(unsigned int nLoops, volatile double *counter, int schedPolicy, int schedPriority) :
	Thread(),nLoops(nLoops), counter(counter)
{
	setScheduling(schedPolicy, schedPriority);
	
}


void IncrementThread::run()
{
	for(unsigned int i=0; i<nLoops; i++)
	{
		(*counter)++;	
	}
	
}

IncrementThread::~IncrementThread()
{
}
