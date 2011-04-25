#ifndef _MUTEX_HPP_
#define _MUTEX_HPP_

#include <iostream>
#include <pthread.h>

using namespace std;

namespace tailio {
	class Mutex {		
	public:
		Mutex(bool logging = true);
		virtual ~Mutex();
		void lock();
		bool trylock();
		void unlock();
	protected:
		pthread_mutex_t mutex;
		bool logging;
	};
	
	class Condition : public Mutex {
	public:
		Condition();
		virtual ~Condition();
		void wait();
		void signal();
		void signalAll();
	protected:
		pthread_cond_t condition;
	};
}

#endif