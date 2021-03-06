#ifndef _THREAD_HPP_
#define _THREAD_HPP_

#include <iostream>
#include <pthread.h>

using namespace std;

namespace tailio {
	class Thread {		
	public:
		typedef void* ReturnValue; 
		typedef void* ArgType;
		Thread(ReturnValue (*run)(void*));
		virtual ~Thread();
		void start(ArgType arg);
		void join(ReturnValue* value = NULL);
	private:
		ReturnValue (*run)(ArgType);
		pthread_t handle;
		bool joined;
	};
}

#endif