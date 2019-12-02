/**@file Timer.h
 * @brief Implements timer class
 */
#ifndef TIMER_INCLUDED
#define TIMER_INCLUDED

#include <signal.h>
#include <time.h>

/**@brief Class timer mimics a timer
 */
class Timer
{
protected:
	/**@brief timer id type returned by timer_create
	 */
	timer_t tid;
	
	/**@brief virtual function that'll allow each class daughter
	 * to implement its own callback characteristic function
	 */
	virtual void callback()=0;
		
public:

	/**@brief Timer Constructor
	 * Configure timer (action and expiration event) and creates it
	 */
	Timer();
	
	/**@brief Timer Destructor
	 * Destroy timer_t tid
	 */
	virtual ~Timer();
	
	/**@brief Start timer
	 * It's specific of each daughter class
	 */
	virtual void start(double duration_ms)=0;
	
	/**@brief Stops timer
	 * Sets itimerspec of timer to zero
	 */
	void stop();

private:

	/**@brief Caller for callback function
	 * It allows to access the callback by sending the callee object 
	 * through pointer void. Which then allows to chose the right callback
	 * Being static allow us to use it without instanciating timer
	 * 
	 * @param si pointer that contains the callee object (timer instance)
	 */
	static void call_callback(int, siginfo_t* si, void*);

};

#endif

