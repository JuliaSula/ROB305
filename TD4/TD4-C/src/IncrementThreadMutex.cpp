#include "IncrementThreadMutex.h"
#include <iostream>
using namespace std;
IncrementThreadMutex::IncrementThreadMutex(unsigned int nLoops, volatile double *counter, int schedPolicy, Mutex *m) :
	Thread(),nLoops(nLoops), counter(counter), m(m)
{
	int schedPriority = sched_get_priority_max(schedPolicy);
	setScheduling(schedPolicy, schedPriority);
}

void IncrementThreadMutex::run()
{
	for(unsigned int i=0; i<nLoops; i++)
	{
		Mutex::Lock Lock(*m);
		(*counter)++;
		
	}

}

IncrementThreadMutex::~IncrementThreadMutex()
{
}

double IncrementThreadMutex::getCounter()
{
	return (*counter);
}
