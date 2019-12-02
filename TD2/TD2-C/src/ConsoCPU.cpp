#include "TimeSpec.h"
#include "SigHandler.h"
#include <math.h>
#include <iostream>
#include "ConsoCPU.h"
#include <limits.h>  // for INT_MAX
using namespace std;

void incr(unsigned int nLoops, double* pCounter)
{
	for(unsigned int i=0; i<nLoops; i++)
	{
		(*pCounter)++;
	}
}

unsigned incr(unsigned int nLoops, double* pCounter, volatile bool* pStop)
{
	unsigned int i=0;
	
	for(i=0; i<nLoops; ++i)
	{
		if(!(*pStop))	
			(*pCounter)++;
		else 
			break;
	}
	return i;

}

void myHandlerBool(int, siginfo_t* si, void*)
{
	volatile bool* count=(volatile bool*)si->si_value.sival_ptr;
	cout<<" [ConsoCPU] Interruption pStop: "<<*count<< endl;
	*count=true;
}

double get_counter( long int delay_s )
{
	unsigned int nLoops(UINT_MAX);
	double		 counter(0);
	volatile bool stop=false;
	struct timespec timeStart_ts;
	struct timespec timeEnd_ts;
	timer_t tid;
	
	tid=init_timer(myHandlerBool,(void*)&stop);
	itimerspec its;
	its.it_value	= {delay_s, 0};
	its.it_interval = {0, 0};
	timer_settime(tid, 0, &its, NULL);
	
	clock_gettime(CLOCK_REALTIME, &timeStart_ts);
	counter=incr(nLoops, &counter, &stop);
	clock_gettime(CLOCK_REALTIME, &timeEnd_ts);

	timer_delete(tid);
	return counter;
}

line calib()
{
	unsigned int i4=get_counter(4);
	unsigned int i6=get_counter(6);
	line lineValue;	

	lineValue.a=(i6-i4)/2;;
	lineValue.b= (long int)i6-lineValue.a*6;
	cout<<" [ConsoCPU] Coefficients a: "<<lineValue.a<<" b: "<<lineValue.b<<endl;
	return lineValue;
}

double get_error (line lineValue, long int t)
{
	unsigned i=get_counter(t);
	cout<<" [ConsoCPU] nLoops:"<<i<<endl;
	long int iCalib=lineValue.a*t+lineValue.b;
	cout<<" [ConsoCPU] estimated nLoops: "<<iCalib<<endl;
	double error= (double)(iCalib-i)/i*100;
	return error;
	
	}


line calibPrecision(int nTest)
{	
	
	unsigned int i4;
	unsigned int i6;
	double a, b;
	line lineValue;	
	for (int i=0; i<nTest; i++)
	{
		i4=get_counter(4);
		i6=get_counter(6);
		a+=(i6-i4)/2;
		b+= (long int)i6-(i6-i4)/2*6;
	}
	cout<<" [ConsoCPU] Coefficients a: "<<a<<" b: "<<b<<endl;
	lineValue.a=a/nTest;
	lineValue.b=b/nTest;
	
	return lineValue;

}


void* call_incr( void* v_data)
{	
	Data* p_data= (Data*) v_data;
	incr(p_data->nLoops, (double*)&(p_data->counter), (bool*)&p_data->stop,(bool*)&p_data->mutexLock, &p_data->mtx );
	
	return v_data;
}

unsigned incr(unsigned int nLoops, double* pCounter, bool* pStop, bool* mutexLock, std::mutex* mtx)
{
	unsigned int i=0;
	
	for(i=0; i<nLoops and not *pStop; ++i)
	{
		if(*mutexLock)
		{
			mtx->lock();
			*pCounter +=1.0 ;
			mtx->unlock();
		}
		else 
		{
			*pCounter +=1.0 ;
		}
	}
	return i;

}
