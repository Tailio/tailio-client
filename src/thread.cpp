#include "log.hpp"
#include "thread.hpp"

using namespace tailio;

Thread::Thread(Thread::ReturnValue (*run)(void*)) : run(run), handle(NULL), joined(false) {
	
}

Thread::~Thread() {
	if (!joined && handle) {
		join(NULL);
	}
}

void Thread::start(ArgType arg) {
	pthread_create(&handle,NULL,run,arg);
	debug("Thread %d started thread %d", pthread_self(), handle);
}


void Thread::join(Thread::ReturnValue* value) {
	if (handle) {
		debug("Thread %d joining thread %d", pthread_self(), handle);
		void** ptr = (value ? value : NULL);
		pthread_join(handle,ptr);
		joined = true;
	}
}