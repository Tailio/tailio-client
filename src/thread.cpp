#include "thread.hpp"

using namespace tailio;

Thread::Thread(Thread::ReturnValue (*run)(void*)) : run(run), handle(NULL) {
	
}

Thread::~Thread() {
	
}

void Thread::start(ArgType arg) {
	pthread_create(&handle,NULL,run,arg);
}


void Thread::join(Thread::ReturnValue* value) {
	if (handle) {
		void** ptr = (value ? value : NULL);
		pthread_join(handle,ptr);
	}
}