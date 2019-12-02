#include <iostream>
#include "TakeThread.h"
#include "PosixThread.h"
#include "GiveThread.h"
#include "Semaphore.h"
#include <errno.h>   // for errno
#include <limits.h>  // for INT_MAX
#include <stdlib.h>  // for strtol
#include <vector>
#include <string.h>
#include <stdio.h>

using namespace std;



int main(int argc, char* argv[]) 
{
	
	unsigned int counter=0;
	unsigned int taken=0;
	unsigned int given=0;
	double execTimeGive=0;
	double execTimeTake=0;
	
 	timespec begin=timespec_now();
 	
	if (argc < 4)	//Avoids segmentation faults, if the arguments 
								//needed by the program are not give
	{
		cout << "No arguments, needs argument nCons, nProds, nTokens"<<endl;
		return 1;
	}
	
		
	Semaphore semaphore;
	unsigned int nCons=stoul(argv[1]);
	unsigned int nProds=stoul(argv[2]);
	unsigned int nTokens=stoul(argv[3]);	
	
	vector<TakeThread> takingThreads(nCons,TakeThread(&semaphore));
	vector<GiveThread> givingThreads(nProds, GiveThread(nTokens, &semaphore));//Pq 1?
		
	
	for (auto &thread : givingThreads) 
	{
		thread.start(); 
	}
		
	for (auto &thread : givingThreads)
	{
		thread.join();
		given+=thread.getGiven();
		execTimeGive += thread.execTime_ms();
	}	
	
	for (auto &thread : takingThreads) 
	{
		thread.start(); 
	}

		
	for (auto &thread : takingThreads)
	{
	
		thread.join();
		taken+=thread.getTaken();
		execTimeTake += thread.execTime_ms();
	}	
	counter=semaphore.getCounter();
	timespec end= timespec_now(); 
	cout<<" [main] Time to run (total time): "<<timespec_to_ms(timespec_subtract(end,begin))/1000<<endl;
	cout<<" [main] nCons: "<<nCons<< "\n [main] nProds: "<<nProds<< endl;
	cout<<" [main] nTokens: " << nTokens << "\n [main] taken: "<<taken<<"\n [main] given: "<<given<<endl;
	cout << " [main] Counter final value: " << counter <<"\n [main] Execution Time Give: "
	<< execTimeGive << "\n [main] Execution Time Take: "<<execTimeTake<<std::endl;
	return 0;
}
