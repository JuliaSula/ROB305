#include "GiveThread.h"
#include <iostream>
using namespace std;

GiveThread::GiveThread(unsigned int nProds,Semaphore* semaphore): nProds(nProds), semaphore(semaphore), given(0)
{
}
	
GiveThread::~GiveThread()
{
}

void GiveThread::run()
{
	for (unsigned int i=0; i<nProds;++i)
	{
		semaphore->give();
		++given;
	}
	
}

unsigned int GiveThread::getGiven()
{
	return given;
}
	
