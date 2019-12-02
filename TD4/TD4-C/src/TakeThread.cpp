#include "TakeThread.h"
#include <iostream>
using namespace std;

TakeThread::TakeThread(Semaphore* semaphore):semaphore(semaphore), taken(0)
{
}
	
TakeThread::~TakeThread()
{
}

void TakeThread::run()
{
	while (semaphore->take(1000)) 
	{
		 taken+=1; 
	}
}
	
unsigned int TakeThread::getTaken()
{
	return taken;
}

