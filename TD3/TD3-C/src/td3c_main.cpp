#include "Calibrator.h"
#include "CpuLoop.h"
#include "Chrono.h"
#include <iostream>
using namespace std;
int main()
{
	
		double samplingPeriod_ms=1000;
		unsigned int nSamples=10;
		double duration_ms=10000;
		Calibrator callibrator(samplingPeriod_ms, nSamples);
		CpuLoop	loop(callibrator);
		
		cout << " [main] Running estimation for 10 seconds "<<endl;
		Chrono chrono;
		loop.runTime(duration_ms);
		chrono.stop();
		
		cout << " [main] Result in seconds: " << chrono.lap()/1000 <<endl;

		return 0;
}
