#include <iostream>
#include "TimeSpec.h"
#include "SigHandler.h"
#include "ConsoCPU.h"
#include <errno.h>   // for errno
#include <limits.h>  // for INT_MAX
#include <stdlib.h>  // for strtol
#include <iostream>
using namespace std;


int main(int argc, char* argv[]) 
{
	
 	timespec begin=timespec_now();
 	
	if (argc < 3)	//Avoids segmentation faults, if the arguments 
								//needed by the program are not give
	{
		cout << "No arguments, needs argument  nLoops and nTasks"<<endl;
		return 1;
	}
	

	unsigned int nLoops= stoul(argv[1]);
	unsigned int nTasks= stoul(argv[2]);
	Data data={false, 0.0, nLoops};
	cout<<" [main] nTasks number: "<<nTasks<<endl;
	cout<<" [main] nLoops number: "<<nLoops<<endl;	


	/************Incr implementation through threads***************/
	

	struct timespec timeNow; 
	timeNow=timespec_now();
	
	
	/********************Thread Creation***************************/
	pthread_t incrementThread[nTasks];
	for(unsigned int i=0; i<nTasks;i++)
	{
		pthread_create(&incrementThread[i], NULL, call_incr, &data);
		cout<<" [main] Thread "<<i<< " created \n"<<flush;
	}
	
	/********************Thread Join*****************************/
	for(unsigned int i=0; i<nTasks;i++)
	{
		pthread_join(incrementThread[i], NULL); // Le main attend le thread pour finir.
		cout<<" [main] Thread "<<i<< " joined \n"<<flush;
	}
	cout<<" [main] Final counter value =  "<<data.counter<<"\n"<<flush;	
	
	timespec end= timespec_now(); 
	cout<<" [main] Time to run: "<<timespec_to_ms(timespec_subtract(end,begin))/1000<<endl;
	cout<<" [main] Time to run: "<<(timespec_to_ms(end)-timespec_to_ms(begin))/1000<<endl;
	return 0;
}
