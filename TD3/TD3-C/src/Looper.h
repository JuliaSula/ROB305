/**@file Looper.h
 * @brief Implements looper class
 */
#ifndef LOOPER_INCLUDED
#define LOOPER_INCLUDED
/**@brief Looper class that increments the loops and allow to 
 * get samples [nLoops, time]
 */
class Looper
{
private:

	/**@brief Defines whether or not iLoops should be incremented
	 */
	bool doStop;
	
	/**@brief Variable that is incremented
	 */
	double iLoop;
	
public:

	/**@brief Static function that allows to call
	 * runLoop without instanciated the class loop
	 * 
	 * @param *v_data: data that is transmitted to function, in
	 * this case loop object
	 */
    static void *callLoop(void *v_data);
	
	/**@brief Increments Loops
	 * Runs incrementation untill it is nLoops or doStop is true
	 * 
	 * @param nLoops: number of loops total
	 * @return value of incremented value after implementation
	 */
	double runLoop(double nLoops);
	
	/**@brief Returns incremented value
	 *
	 * @return value of incremented value
	 */
	double getSamples();
	
	/**@brief Stops increment
	 * Turns doStop into true 
	 * 
	 * @return incremented value after  stop
	 */
	double stopLoop();
};
#endif
