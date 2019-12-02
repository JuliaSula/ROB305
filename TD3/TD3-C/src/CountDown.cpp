#include "CountDown.h"
#include <iostream>
using namespace std;
Countdown::Countdown(int n) : counter(n) {}

	
void Countdown::callback()
{
	--counter;
	std::cout << " [Countdown] Counter "<< counter << std::endl;

	if (counter == 0)
	{
		stop();
	}

}
