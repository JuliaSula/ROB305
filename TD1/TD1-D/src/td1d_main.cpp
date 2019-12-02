#include "ConsoCPU.h"
#include "SigHandler.h"
#include "TimeSpec.h"
#include <limits.h>
#include <iostream>
using namespace std;
int main() {
	
	/***********Test Function Incr********************/
	unsigned int nLoops(UINT_MAX);
	double		 counter(0);
	volatile bool stop=false;
	struct timespec timeStart_ts;
	struct timespec timeEnd_ts;
	timer_t tid;
	
	tid=init_timer(myHandlerBool,(void*)&stop);
	itimerspec its;
	its.it_value	= {1, 0};
	its.it_interval = {0, 0};
	timer_settime(tid, 0, &its, NULL);
	
	clock_gettime(CLOCK_REALTIME, &timeStart_ts);
	int loops=incr(nLoops, &counter, &stop);
	clock_gettime(CLOCK_REALTIME, &timeEnd_ts);

	timer_delete(tid);
	
	/***********Test Function Calib*******************/
	
	line lineValue= calib();
	double error=get_error(lineValue, 3);
	cout <<" [main] Error between estimated nLoops and nLoops "
		<< error<<"%"<< endl;
	
	int execTime_ms=timespec_to_ms(timeEnd_ts-timeStart_ts);
	int estimatedLoops=(double)lineValue.a*execTime_ms/1000+lineValue.b;
	cout <<" [main] estimatedLoops :"
		<< estimatedLoops<<" loops :" <<loops << " Ratio (loops/estimatedLoops) "<< (double)loops/estimatedLoops<< endl;
}
