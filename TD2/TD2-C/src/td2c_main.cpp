#include <iostream>
#include "TimeSpec.h"
#include "SigHandler.h"
#include "ConsoCPU.h"
#include <errno.h>   // for errno
#include <limits.h>  // for INT_MAX
#include <stdlib.h>  // for strtol
#include <string>
#include <vector>

//Mutex guarantee the variable integrity when in parallel configuration
//One should reduce to the maximum the size of the shared data, for it is slow to give or lock acess 

using namespace std;

int main(int argc, char* argv[]) 
{
	volatile double counter=0.0;//Counter must be volatile or the final counter final will not be guarantee to be right
	bool pStop=false;
	bool mtxLock=false;
	Data dataStruct;
	
 	if (argc < 4)	//Avoids segmentation faults, if the arguments 
								//needed by the program are not give
	{
		cout << "No arguments, needs argument nLoops, nTask and protected(y/n)"<<endl;
		return 1;
	}
	/****************Variables initialization***********************************/
	unsigned int nLoops= stoul(argv[1]);
	unsigned int nTasks= stoul(argv[2]);
	std::string arg3(argv[3]);
	
	dataStruct.stop=pStop;
	dataStruct.counter=counter;
	dataStruct.nLoops=nLoops;
  
	/***************Check if it'll run protected or not************************/
	if(arg3=="y")
	{
		mtxLock=true;
	}
		
	/**************Thread initialization using vectors************************/ 
	vector<pthread_t> incrementThread(nTasks);
	
	struct timespec timeStart_ts;
	struct timespec timeEnd_ts;
	clock_gettime(CLOCK_REALTIME, &timeStart_ts);
	
	for(vector<pthread_t>::iterator it=incrementThread.begin();it!=incrementThread.end();it++)
	{
		pthread_create(&(*it), NULL, call_incr, &dataStruct);
	}
		
	for(std::vector<pthread_t>::iterator it =incrementThread.begin(); it!=incrementThread.end();it++)
	{
		pthread_join(*it, NULL);
	}
	
	clock_gettime(CLOCK_REALTIME, &timeEnd_ts);
	
	double timeExec_s=timespec_to_ms(timespec_subtract(timeEnd_ts,timeStart_ts))/1000; 
	cout<<" [main] Protected =  "<< mtxLock <<"\n"<<flush;
	cout<<" [main] Counter value=  "<<dataStruct.counter<<"\n"<<flush;
	cout<<" [main] Time to run: "<<timeExec_s<<endl;
	return 0;
}
