/**@file Semaphore.h
 * @brief Implements a semaphore class
 */

#ifndef SEMAPHORE_INCLUDED
#define SEMAPHORE_INCLUDED

#include "Mutex.h"
#include <limits>
#include <pthread.h>

/**@brief The semaphore is a token box
 * the number of tokens is the counter, and it can gives or take tokens
 */
class Semaphore
{
private:
	/**@brief variable that represents number of tokens the semaphore has
	 */
	unsigned int counter;
	
	/**@brief Number maximum of tokens a semaphore can have
	 */
	unsigned int maxCounter;
	
	/**@brief Mutex that will allowed coordinated access to counter
	 */
	Mutex m;
public:

	/**@brief Semaphore constructor 
	 * Sets initial counter number between minimum and maximum number of tokens
	 * 
	 * @param initCount: minimum number of tokens
	 * @param maxCounte: maximum number of tokens
	 */
	Semaphore(unsigned int initCount=0, unsigned int maxCount=std::numeric_limits<unsigned int>::max());
	
	
	/**@brief Semaphore destructor
	 */
	~Semaphore();
	
	/**@brief Decrements the number of tokens of the semaphore
	 */
	void give();
	
	/**@brief Increments the number of tokens of the semaphore
	 */
	void take();
	
	/**@brief Increments the number of tokens of the semaphore
	 * if it acquires mutex before time-out
	 * 
	 * @param timeout_ms: absolute waiting time in ms
	 * @return true if mutex was acquired and tokens incremented, false otherwise
	 */
	bool take(double timeout_ms);
	
	/**@brief Gets number of tokens
	 * 
	 * @return counter value: number of tokens in the semaphore
	 */
	unsigned int getCounter();
};
#endif
