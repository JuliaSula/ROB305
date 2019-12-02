#include "TimeSpec.h"
#include <math.h>
#include <iostream>
using namespace std;

double timespec_to_ms(const timespec& time_ts)
{
	double time_ms;
	time_ms=time_ts.tv_sec*1.e3;
	time_ms+=time_ts.tv_nsec/1.e6;
	return time_ms;
}

timespec timespec_from_ms(double time_ms)
{
    struct timespec time_ts;
	time_ts.tv_sec=floor(time_ms/1.e3);
	time_ts.tv_nsec=(-time_ts.tv_sec*1.e3+time_ms)*1.e6;
	return time_ts;
}


timespec timespec_now()
{
	struct timespec timeNow; 
	clock_gettime(CLOCK_REALTIME, &timeNow);
	return timeNow;
}


timespec timespec_negate(const timespec& time_ts)
{
	struct timespec timeNegate; 
	if(time_ts.tv_nsec!=0){
		timeNegate.tv_nsec=1.e9-time_ts.tv_nsec;
		timeNegate.tv_sec=-time_ts.tv_sec-1;
	} 
	else
		timeNegate.tv_sec=-time_ts.tv_sec;	
	return timeNegate;	 
}

timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts)
{
	struct timespec timeAdded; 
	double nsec, sec;
	nsec=time1_ts.tv_nsec+time2_ts.tv_nsec;
	if(nsec>=1.e9)	
	{
		nsec=nsec-1.e9;
		sec=time1_ts.tv_sec+time2_ts.tv_sec+1;
	}
	else
		sec=time1_ts.tv_sec+time2_ts.tv_sec;
	timeAdded.tv_sec=sec;
	timeAdded.tv_nsec=nsec;
	return timeAdded;
}



timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts)
{
	struct timespec timeSubtracted;
	double nsec, sec;
	nsec=time1_ts.tv_nsec-time2_ts.tv_nsec;
	if(nsec<=0)	
	{
		nsec=nsec+1.e9;
		sec=time1_ts.tv_sec-time2_ts.tv_sec-1;
	}
	else
		sec=time1_ts.tv_sec-time2_ts.tv_sec;
	timeSubtracted.tv_sec=sec;
	timeSubtracted.tv_nsec=nsec;
	return timeSubtracted; 
}




timespec timespec_wait(const timespec& delay_ts)
{
	struct timespec remainingTime_ts;	
	
    nanosleep(&delay_ts, &remainingTime_ts);
	
	return remainingTime_ts;
}

timespec  operator- (const timespec& time_ts)
{
	return timespec_negate(time_ts);
}

timespec  operator+ (const timespec& time1_ts, const timespec& time2_ts)
{
	return timespec_add(time1_ts, time2_ts);
}

timespec  operator- (const timespec& time1_ts, const timespec& time2_ts)
{
	return timespec_subtract(time1_ts, time2_ts);
}

timespec& operator+= (timespec& time_ts, const timespec& delay_ts)
{
	time_ts=time_ts+delay_ts;
	return time_ts;
}

timespec& operator-= (timespec& time_ts, const timespec& delay_ts)
{
	time_ts=time_ts-delay_ts;
	return time_ts;
}


bool operator== (const timespec& time1_ts, const timespec& time2_ts)
{
	return (timespec_to_ms(time1_ts)==timespec_to_ms(time2_ts));
}


bool operator!= (const timespec& time1_ts, const timespec& time2_ts)
{
	return (timespec_to_ms(time1_ts)!=timespec_to_ms(time2_ts));
}

bool operator< (const timespec& time1_ts, const timespec& time2_ts)
{
	return (timespec_to_ms(time1_ts)<timespec_to_ms(time2_ts));
}

bool operator> (const timespec& time1_ts, const timespec& time2_ts)
{
	return (timespec_to_ms(time1_ts)>timespec_to_ms(time2_ts));
}



//timer prototype based in timespec
void timer(float frequency)
{
	float t_ms=1/frequency*1000;
	struct timespec t_ts=timespec_from_ms(t_ms);
	struct timespec remainingTime_ts;
	for(int i=0; i<15; i++)
	{
		cout<<" [TimeSpec] counter "<< i<<endl;
		nanosleep(&t_ts,&remainingTime_ts);
	}

}
