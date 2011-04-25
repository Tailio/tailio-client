#include <vector>

#include <gtest/gtest.h>

#include "mutex.hpp"
#include "thread.hpp"

using namespace std;
using namespace tailio;

class ThreadTest : public ::testing::Test {
	
};

void* goRun(void* arg) {
	long result = (long) arg;
	return (void*) (result + 1);
}

TEST_F(ThreadTest,Go) {
	tailio::Thread thread(goRun);
	long x = 42, got = 0;
	thread.start((void*) x);
	thread.join((void**) &got);
	ASSERT_EQ(x + 1, got);
}



struct ConditionTestContext {
	int threadCount;
	
	int readyCount;
	Condition allReady;

	bool greenLight;
	Condition greenLightCondition;

	int doneCount;
	Condition allDone;
};

void* conditionTestGo(void* pArg) {
	debug("Thread %d started",pthread_self());
	ConditionTestContext* pContext = (ConditionTestContext*) pArg;
	
	pContext->allReady.lock(); {
		pContext->readyCount++;
		if (pContext->readyCount == pContext->threadCount) {
			pContext->allReady.signal();
		}
	} pContext->allReady.unlock();
	
	pContext->greenLightCondition.lock(); {
		while (!pContext->greenLight) {
			pContext->greenLightCondition.wait();
		}
	} pContext->greenLightCondition.unlock();
	
	pContext->allDone.lock(); {
		pContext->doneCount++;
		if (pContext->doneCount == pContext->threadCount) {
			pContext->allDone.signal();
		}
	} pContext->allDone.unlock();
	return NULL;
}


TEST_F(ThreadTest,Condition) {
	typedef vector<Thread*> ThreadList;
	ThreadList threadList;
	ConditionTestContext context;
	context.greenLight = false;
	context.doneCount = 0;
	context.readyCount = 0;
	context.threadCount = 10;
	
	
	for (int i = 0; i < context.threadCount; i++) {
		Thread* pThread = new Thread(conditionTestGo);
		threadList.push_back(pThread);
		pThread->start(&context);
	}

	debug("cha");
	
	context.allReady.lock(); {
		while (context.readyCount != context.threadCount) {
			context.allReady.wait();
		}
	} context.allReady.unlock();
	
	EXPECT_EQ(context.threadCount,context.readyCount);
	
	context.allDone.lock(); {
		context.greenLightCondition.lock(); {
			context.greenLight = true;
			context.greenLightCondition.signalAll();
		} context.greenLightCondition.unlock();
		
		while (context.doneCount != context.threadCount) {
			context.allDone.wait();
		}
	} context.allDone.unlock(); 
	
	EXPECT_EQ(context.threadCount,context.doneCount);
	
	for (int i = 0; i < context.threadCount; i++) {
		delete threadList[i];
		threadList[i] = NULL;
	}
}