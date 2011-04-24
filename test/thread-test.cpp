
#include <gtest/gtest.h>
#include "thread.hpp"



void* goRun(void* arg) {
	long result = (long) arg;
	return (void*) (result + 1);
}

TEST(ThreadTest,Go) {
	tailio::Thread thread(goRun);
	long x = 42, got = 0;
	thread.start((void*) x);
	thread.join((void**) &got);
	ASSERT_EQ(x + 1, got);
}

