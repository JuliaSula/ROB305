#include "Looper.h"
#include <cfloat>
#include <limits>
#include <iostream>

using namespace std;
double Looper::runLoop(double nLoops)
{
	doStop = false;
	iLoop  = 0;
	for (int k = 0; k < nLoops; k++)
	{
		//cout<<"[Looper] iLoop: "<<iLoop<<endl;
		iLoop++;
		if (doStop)  
			break; 
	}

	return iLoop;
}

void *Looper::callLoop(void *v_data)
{
		Looper *loop = (Looper*)(v_data);
		loop->runLoop(std::numeric_limits<double>::max());

		return nullptr;
}

double Looper::getSamples()
{
	return iLoop;
}

double Looper::stopLoop()
{
	doStop = true;
	return iLoop;
}

