
/* * @file TimeSpec.h
 *   @brief Function implementation based in Timespec structure
 */

#ifndef TimeSpec_h_INCLUDED
#define TimeSpec_h_INCLUDED

#include <time.h>
#include <signal.h>


/** @brief Converts timespec struct to miliseconds
 * 
 * @param time_ts timespec structure to be converted
 * @return miliseconds (double)
 */
double timespec_to_ms(const timespec& time_ts);

/**@brief Converts miliseconds to timespec structure
 * 
 * @param time_ms double to be converted
 * @return a timespec structure
 */
timespec timespec_from_ms(double time_ms);

/**@brief Return current time
 * Uses a fonction from time.h library in order to turn CLOCK_REALTIME, 
 * a system variable into a timespec structure
 * 
 * @return timespec structure representing current time
 */
timespec timespec_now();

/**@brief Returns timespec times -1
 * Considering timespec structure contraints, turns a timespec to its opposite
 * 
 * @param time_ts a timespec structure
 * @return a timespec structure (- @p time_ts)
 */  
timespec timespec_negate(const timespec& time_ts);

/**@brief Returns the addition between two timespec structure
 * Sums between to timespec structures that are given as parameters
 * 
 * @param time1_ts timespec structure to be added
 * @param time2_ts timespec structure to be added
 * @return a timespec structure ( @p time1_ts + @p time2_ts)
 */
timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts);

/**@brief Returns the subtraction between two timespec structure
 * Subtraction between to timespec structures that are given as parameters
 * 
 * @param time1_ts timespec structure from which to subtract
 * @param time2_ts timespec structure to subtract
 * @return a timespec struct ( @p time1_ts - @p time2_ts)
 */
timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts);

/**@brief Applies a waiting period 
 * Uses the value of a timespec structure in order to make the program pause for  
 * specified amount of time
 * 
 * @param delay_ts timespec structure
 * @return the remaining time to be waited
 */
timespec timespec_wait(const timespec& delay_ts);

/**@brief Operation that returns '-' timespec
 * Return the value of a timespec structure turned negative
 * 
 * @param time_ts timespec structure to be converted
 * @return timespec structure (- @p time_ts)
 */
timespec  operator- (const timespec& time_ts);

/**@brief Returns the addition of two number
 * Defines '+' operation between two timespec structures
 * 
 * @param time1_ts timespec structure to be added
 * @param time2_ts timespec structure to be added
 * @return timespec structure ( @p time1_ts + @p time2_ts)
 */ 
timespec  operator+ (const timespec& time1_ts, const timespec& time2_ts);

/**@brief Returns the subtraction of two number
 * Defines '-' operation between two timespec structures
 * 
 * @param time1_ts timespec structure from which to subtract
 * @param time2_ts timespec structure to subtract
 * @return timespec structure ( @p time1_ts - @p time2_ts)
 */
timespec  operator- (const timespec& time1_ts, const timespec& time2_ts);

/**@brief Increments timespec value by a given argument
 * Turn timespec time_ts into time_ts plus delay_ts
 * 
 * @param time_ts timespec structure that will be modified (incremented by delay_ts)
 * @param delay_ts timespec structure that will increment time_ts
 * value that'll be added to time_ts
 * 
 * @return the modified timespec structure of @p time_ts ( @p time_ts= @p time_ts+ @p delay_ts)
 */ 
timespec& operator+= (timespec& time_ts, const timespec& delay_ts);

/**@brief Decrements timespecs value by a given argument
 * Turns timespec structure time_ts into time_ts minus delay_ts
 * 
 * @param time_ts timespec structure to be decremented
 * @param delay_ts timespec structure value to decrement time_ts
 * @return the decremented timespec structure of @p time_ts (@p time_ts= @p time_ts - @p delay_ts)
 */
timespec& operator-= (timespec& time_ts, const timespec& delay_ts);

/**@brief Returns true if timespec argument are equal
 * Comparison between two timespec structures
 * 
 * @param time1_ts timespec structure to compare
 * @param time2_ts timespec structure to compare
 * @return bool value (true if @p time1_ts = @p time2_ts, 
 * false if @p time1_ts!= @p time2_ts)
 */
bool operator== (const timespec& time1_ts, const timespec& time2_ts);

/**@brief Returns true if timespec argument are different
 * Comparison between two timespec structures
 * 
 * @param time1_ts timespec structure to compare
 * @param time2_ts timespec structure to compare
 * @return bool value (false if @p time1_ts = @p time2_ts, 
 * true if @p time1_ts!= @p time2_ts)
 */
bool operator!= (const timespec& time1_ts, const timespec& time2_ts);

/**@brief Returns true if timespec argument is greater than the other
 * Comparison between two timespec structures
 * 
 * @param time1_ts timespec structure to compare
 * @param time2_ts timespec structure to compare
 * @return bool value (true if @p time1_ts > @p time2_ts, 
 * false if @p time1_ts < @p time2_ts)
 */
bool operator< (const timespec& time1_ts, const timespec& time2_ts);

/**@brief Returns true if timespec argument is smaller than the other
 * Comparison between two timespec structures
 * 
 * @param time1_ts timespec structure to compare
 * @param time2_ts timespec structure to compare
 * @return bool value (true if @p time1_ts < @p time2_ts, 
 * false if @p time1_ts > @p time2_ts)
 */
bool operator> (const timespec& time1_ts, const timespec& time2_ts);

/**@brief Prototype of a timer function based in the timespec structure
 * 
 * @param frequency that will be the timer frequency
 */
void timer(float frequency);


#endif
