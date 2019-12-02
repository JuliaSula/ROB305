/**@file Thread.h
 * @brief Implements Thread class derived from posixThread
 */

#ifndef THREAD_INCLUDED
#define THREAD_INCLUDED

#include "PosixThread.h"
#include "Chrono.h"

/**@brief Thread classic mimic a thread 
 * Adds time measures for thread execution
 */
class Thread: public PosixThread
{
private:
	/**@brief Chrono object that allows to perform 
	 * time measures
	 */
	Chrono chrono;
	
	/**@brief Static function that allows to call
	 * run function without instantiating a thread
	 * 
	 * @param *vthread: data to be transmitted to run
	 * function
	 */
	static void *callrun(void *v_thread);
public:

	/**@brief Thread constructor
	 */
	Thread();
	
	/**@brief Thread destructor
	 */
	~Thread();
	
	/**@brief Runs a function in a thread
	 */
	void start();
	
	/**@brief Pauses the thread for a certaint time
	 * 
	 * @param delay_ms: sleeping/pausing time for the thread
	 */
	void sleep_ms(double delay_ms);
	
	/**@brief Begining of the task execution
	 * Starts chrono as the task starts execution
	 * 
	 * @return time that the task started
	 */
	double startTime_ms();
	
	/**@brief End of the task execution
	 * Stops chrono as the task stops execution
	 * 
	 * @return time that the task stoped
	 */
	double stopTime_ms();
	
	/**@brief Execution time
	 * Time between the start and the end of the execution
	 * 
	 * @return task execution time
	 */
	double execTime_ms();
protected:

	/**@brief Virtual function that will allow each derived thread
	 * to run its own characteristic function
	 */
	virtual void run()=0;
	

};

#endif
