#include "Calibrator.h"
#include <pthread.h>
#include <iostream>
#include <math.h>
using namespace std;
Calibrator::Calibrator(double samplingPeriod_ms, unsigned int nSamples) :
	samples({}), counter(nSamples)
{
	Looper localLooper{};
	looper = &localLooper;

	pthread_t threadId;
	pthread_create(&threadId,  NULL, looper->callLoop, looper);
	start(samplingPeriod_ms);
	pthread_join(threadId, NULL);

	looper = NULL;


	Calibrator::LinearRegression(samples, nSamples,
									samplingPeriod_ms);
									

	
	
}

void Calibrator::LinearRegression(std::vector<double> samples,
								 unsigned nSamples, double samplingPeriod_ms)
{
	double mean = 0;
	
	for (unsigned i=0;i<nSamples;i++)
	{
		mean+=samples[i]/nSamples;
	}	
	double mean_t = samplingPeriod_ms * (nSamples + 1) / 2;         
    
    double squaredError=0;
    double errorXY=0;
    double t=0;
    
    for (unsigned i=0;i<nSamples;i++)
    {
		t+=samplingPeriod_ms;
		squaredError += pow((t - mean_t),2);
		errorXY += (samples[i] - mean)*(t - mean_t);
	}
	
	lineValue.a = errorXY/squaredError;
	lineValue.b = mean - lineValue.a*mean_t;	
}


double Calibrator::nLoops(double duration_ms) 
{
	return lineValue.a * duration_ms + lineValue.b; 
}

void Calibrator::callback()
{
		--counter;

		if (counter == 0)
		{
				samples.push_back(looper->stopLoop());
				stop();
		}
		else
		{
				samples.push_back(looper->getSamples());
		}
}
