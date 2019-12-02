/**@file Countdown.h
 * @brief Implements class Countdown
 */

#ifndef COUNTDOWN_INCLUDED
#define COUNTDOWN_INCLUDED

#include "PeriodicTimer.h"

/**
 * @brief A class that implements a countdown
 */
class Countdown : public PeriodicTimer
{
	public:
		/**@brief counter
		 * Variable that'll be used for the countdown
		 */
		int counter;

	public:
		/** @brief Coundown Constructor
		 *
		 * @param n: counter will be set to n
		 */
		Countdown(int n);

	protected:
		/** @brief Callback function that specifies the timer characteristic
		 */
		void callback();
};

#endif
