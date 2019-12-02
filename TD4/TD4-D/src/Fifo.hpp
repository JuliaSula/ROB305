/**@file Fifo.h
 * @brief Implements fifo class 
 */
#ifndef FIFO_INCLUDED
#define FIFO_INCLUDED

#include "Mutex.h"
#include <exception>
#include <queue>
#include <string>


/**@brief class Fifo: first in, first out functionality
 */
template <typename T> class Fifo
{
private:

	/**@brief Queue of elements stored in a fifo
	 */
	std::queue<T> elements;

	/**@brief Mutex to organize access to fifo
	 */
	Mutex m;

public:

	/**@brief Exception to throw when fifo is empty
	 */
	class EmptyException : std::exception
		{
			public:
				const char *what() const noexcept;
		};
public:
	
	/**@brief Fifo Constructor
	 */
	Fifo();
	
	/**@brief Fifo Destructor
	 */
	~Fifo();
	
	/**@brief Pushes an element into fifo
	 * Adds a new elements to fifo
	 * 
	 * @param element: to be pushed into fifo
	 */
	void push(T element);
	
	/**@brief Pops an element out of the fifo
	 * 
	 * @return T element
	 */
	T pop();
	
	/**@brief Pops an element out of the fifo with time-out
	 * If it has access to fifo before time-out pops the element
	 * else it does not
	 * 
	 * @return T element
	 */
	T  pop(double timeout_ms);
	
	int get_FifoSize();

};

template <typename T> Fifo<T>::Fifo() : elements(), m()
{
}



template <typename T> T Fifo<T>::pop()
{
	Mutex::Lock lck(m);
	while (elements.size()==0)
	{
		lck.wait();
	}
	T elements= elements.front();
	elements.pop();
	return elements;
	
}

template <typename T> T Fifo<T>::pop(double timeout_ms) 
{
	Mutex::Lock lck(m);
	if (elements.size() == 0) 
	{
		lck.wait(timeout_ms);											//Blocking call if fifo is empty
	}
	if (elements.size() > 0)
	{
		T element = elements.front();
		elements.pop();
		return element;
	}
	else
	{
		throw Fifo<T>::EmptyException();
	}

} 


template <typename T> void Fifo<T>::push(T element)
{
		Mutex::Lock lck(m); 
		elements.push(element);
}

template <typename T> const char *Fifo<T>::EmptyException::what() const noexcept
{
		return "Timed out";
}

template <typename T> Fifo<T>::~Fifo()
{
}

template <typename T> int Fifo<T>::get_FifoSize()
{
	return elements.size();
	}
#endif
