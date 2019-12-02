#include <iostream>
#include "IncrementThread.h"
#include "PosixThread.h"
#include <errno.h>   // for errno
#include <limits.h>  // for INT_MAX
#include <stdlib.h>  // for strtol
#include <vector>
#include <string.h>
#include <stdio.h>


using namespace std;



int main(int argc, char* argv[]) 
{
	
	
	volatile double counter=0.0;
	int schedPolicy(SCHED_OTHER);
	int policy=0;
	int priority=0;
	double execTime;
	
 	timespec begin=timespec_now();
 	
	if (argc < 2)	//Avoids segmentation faults, if the arguments 
								//needed by the program are not give
	{
		cout << "No arguments, needs argument nTasks, nLoops, schedPolicy"<<endl;
		return 1;
	}

	unsigned int nTasks=stoul(argv[1]);
	unsigned int nLoops=stoul(argv[2]);
	if (argc > 3)
	{
		if(!strcmp(argv[3], "SCHED_RR"))
		{
			schedPolicy=SCHED_RR;
		}
		else if(!strcmp(argv[3], "SCHED_FIFO"))
		{
			schedPolicy=SCHED_FIFO;
		}
	}
		
	
	int schedPriority = sched_get_priority_max(schedPolicy);
		
	vector<IncrementThread> incrementThreads(nTasks, IncrementThread(nLoops, &counter, schedPolicy, schedPriority));
	
	for (auto &thread : incrementThreads) 
	{
		thread.start(); 	
	}
		
	incrementThreads[0].getScheduling(&policy, &priority);
		
	for (auto &thread : incrementThreads)
	{
		thread.join();
		execTime += thread.execTime_ms();
	}	
	

	timespec end= timespec_now(); 
	cout<<" [main] Time to run (total time program): "<<timespec_to_ms(timespec_subtract(end,begin))/1000<<endl;
	cout<<" [main] nLoops: "<<nLoops<< "\n [main] nTasks: "<<nTasks<< endl;
	cout<<" [main] Policy: " << policy << "\n [main] Priority: " << priority << endl;
	cout << " [main] Counter final value: " << counter <<"\n [main] Execution Time: "<< execTime << "s" << std::endl;
	return 0;
}
