#include <iostream>
#include "TimeSpec.h"
#include "SigHandler.h"
using namespace std;

int main() 
{
	
	timer_t tid;
	volatile int compteur=0;
	
	//Definition of a 2 Hz timer that counts to 15
	tid=init_timer(myHandler,(void*)&compteur);
	itimerspec its;
	its.it_value.tv_sec=1;
	its.it_value.tv_nsec=0;
	its.it_interval.tv_sec=0;
	its.it_interval.tv_nsec=5.e8;
	timer_settime(tid, 0, &its, NULL);
	
	while(compteur<=15)
	{
    	continue; 
    }
	timer_delete(tid);

}

