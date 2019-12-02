/**@file ConsoCPU.h
 * @brief Implements increments functions for timers and calibration
 * coefficients that allow to now how many loops in how much time
 */
#ifndef ConsoCPU_h_INCLUDED
#define ConsoCPU_h_INCLUDED
#include <time.h>
#include <signal.h>

/**@brief Struct in order to pass line coefficients
*/
struct line{
long int a;
long int b;
};

/**@brief Increments a counter nLoops times
 * 
 * @param nLoops number of times the counter should be incremented
 * @param pCounter pointer to the counter to be incremented
 */
void incr(unsigned int nLoops, double* pCounter);

/**@brief Increments a counter until a stop is demanded
 * The argument bool pStop is changed by a expiration timer, 
 * theferore the counter is incremented untill the timer 
 * expiration
 * 
 * @param nLoops number of times the counter can be incremented
 * @param pCounter pointer to the counter to be incremented
 * @param pStop condition that defines whether the incrementing should 
 * continue or not
 * @return Returns number of times the counter was incremented
 */
unsigned incr(unsigned int nLoops, double* pCounter, volatile bool* pStop);

/**@brief Changes the pointer data to true
 * Action to be done in the timer expiration, it modifies the value pointed by
 * the pointer data to true
 * 
 * @param siginfo_t* si data structure containing signal information
 * from the timer
 */
void myHandlerBool(int, siginfo_t* si, void*);

/**@brief Calculates the coefficients that relates time to number of loops
 * Performing the incrementing function for different timers, the number of 
 * loops is used to calculate the line coefficient such as nLoops=a*t+b
 * 
 * @return line structure which contains a and b
 */
line calib();

/**@brief Calculates error of the estimation by line coefficients
 * Performs an increment function for a new timer, calculates the estimated
 * nLoops and compares it to the real nLoop 
 * 
 * @param lineValue line structure which contains coeff a and b
 * @param t long int that indicates timer expiration time
 * @return error double that is error=(estimatedNLoops-nLoops)/nLoops*100)
 */
double get_error(line lineValue, long int t);

#endif
