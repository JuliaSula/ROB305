/**@file Calibrator.h
 * @brief Implementes class Calibrator 
 */

#ifndef CALIBRATOR_INCLUDED
#define CALIBRATOR_INCLUDED

#include "Looper.h"
#include "PeriodicTimer.h"

#include <array>
#include <vector>
using namespace std;

/**@brief Struct in order to pass line coefficients
	*/
	struct line{
	double a;
	double b;
	};

/**@brief Class that performs the calibration function
 * It allows us to calculate line coefficients a and b 
 */
class Calibrator : PeriodicTimer
{

private:
	
	
	/**@brief Struct of line coefficients
	 */
	 line lineValue;
	/**@brief Vector that will contain the samples (y,x):nLoops, time
	 */
	vector<double> samples{};
	
	/**@brief Counter: variable that'll be incremented
	 */
	unsigned int counter;
	
	/**@brief Pointer to the object responsable for doing the loop incrementation
	 */
	Looper *looper = nullptr;

public:
	
	/**@brief Calibrator constructor
	 * It initializes the calibrator : starts a timer, obtains samples, calculates
	 * a and b coefficients
	 * 
	 * @param samplingPeriod_ms: timer interval period (1/frequency *1000)
	 * @param nSamples: number of samples to be obtained
	 */
	Calibrator(double samplingPeriod_ms, unsigned int nSamples);

	/**@brief Calculates estimated nLoops
	 * 
	 * @param duration_ms: time duration for which to estimate number of loops
	 * @return estimated nLoops (a*t+b)
	 */
	double nLoops(double duration_ms);

protected:
	/** @brief Callback function that specifies the calibrator timer characteristic
		 */
	void callback();

private:

	/** @brief Calculates coefficients a and b through linear regression
	 * 
	 * @param samples: vector of samples [nLoops, time]
	 * @param nSamples : number of samples to be used in linear regression
	 * @param samplingPeriod_ms: timer interval period (1/frequency *1000)
	 */
	void LinearRegression(std::vector<double> samples,
								 unsigned nSamples, double samplingPeriod_ms);
};

#endif
