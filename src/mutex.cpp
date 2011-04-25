#include "log.hpp"
#include "mutex.hpp"

using namespace tailio;


Mutex logMutex(false);

pthread_t self() {
	return pthread_self();
}

Mutex::Mutex(bool logging) : logging(logging) {
	pthread_mutex_init(&mutex,NULL);
#ifdef _DEBUG_
	if (logging) {
		debug("Created mutex %d",&mutex);
	}
#endif
}


Mutex::~Mutex() {
#ifdef _DEBUG_
	if (logging) {
		debug("Destroying mutex %d",&mutex);
	}
#endif
	pthread_mutex_destroy(&mutex);
}

void Mutex::lock() {
#ifdef _DEBUG_
	if (logging) {
		debug("Thread %d Locking mutex %d",self(),&mutex);
	}
#endif
	pthread_mutex_lock(&mutex);
#ifdef _DEBUG_
	if (logging) {
		debug("Thread %d Locked mutex %d",self(),&mutex);
	}
#endif
}


bool Mutex::trylock() {
	int rc = pthread_mutex_trylock(&mutex);
	bool result = (rc == 0);
#ifdef _DEBUG_
	if (logging) {
		debug("Thread %d Try lock mutex %d: %s",self(),&mutex,(result ? "success" : "fail"));
	}
#endif
	return result;
}


void Mutex::unlock() {
	pthread_mutex_unlock(&mutex);
#ifdef _DEBUG_
	if (logging) {
		debug("Thread %d Unlocked mutex %d",self(),&mutex);
	}
#endif
}




Condition::Condition() {
	pthread_cond_init(&condition,NULL);
	debug("Created condition %d",&condition);	
}


Condition::~Condition() {
	debug("Destroying condition %d",&condition);
	pthread_cond_destroy(&condition);
}

void Condition::wait() {
	debug("Thread %d Waiting on condition %d",self(),&condition);
	pthread_cond_wait(&condition,&mutex);
	debug("Thread %d Woke up on condition %d",self(),&condition);
}

void Condition::signal() {
	debug("Thread %d Signaling condition %d",self(),&condition);
	pthread_cond_signal(&condition);
}

void Condition::signalAll() {
	debug("Thread %d Signaling all condition %d",self(),&condition);
	pthread_cond_broadcast(&condition);
}
