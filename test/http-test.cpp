#include <iostream>

#include <gtest/gtest.h>


#include "http.hpp"
#include "log.hpp"
#include "socket.hpp"
#include "thread.hpp"

using namespace std;
using namespace tailio;

void* httpServerRun(void* pArg);

const int port = 31422;


struct HttpServerContext {
	ServerSocket* pServer;
	void (*socketCallback)(Socket*);
};


class HttpTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		debug("setup HttpTest");
		pServer = new ServerSocket(port);
		pThread = new Thread(httpServerRun);
		pContext = new HttpServerContext();
	}
	
	virtual void TearDown() {
		debug("tearDown HttpTest");
		if (pServer) {
			pServer->close();
			delete pServer;
		}
		
		if (pThread) {
			pThread->join();
			delete pThread;
		}
		
		if (pContext) {
			delete pContext;
		}
	}

	void start(void (*socketCallback)(Socket*)) {
		pContext->pServer = pServer;
		pContext->socketCallback = socketCallback;
		pThread->start(pContext);
	}
	
	ServerSocket* pServer;
	Thread* pThread;
	HttpServerContext* pContext;
	
};



void* httpServerRun(void* pArg) {
	HttpServerContext* pContext = (HttpServerContext*) pArg;
	ServerSocket* pServer = pContext->pServer;
	debug("starting server");
	Socket* pSocket = pServer->accept();
	while (pSocket) {
		if (pContext->socketCallback) {
			pContext->socketCallback(pSocket);
		} else {
			debug("No socket handler!!");
		}
		pServer->close(pSocket);
		pSocket = pServer->accept();
	}
	
	debug("ending server");
	return NULL;
}

const string TEST1_MSG = "touche, salesman\n";

void test1HttpHandleSocket(Socket* pSocket) {
	int len = 1024;
	char buffer[len];
	int read = pSocket->receive(buffer,len);
	buffer[read] = 0;
	pSocket->send(TEST1_MSG.c_str(),TEST1_MSG.length());
}

TEST_F(HttpTest,Test1) {
	start(test1HttpHandleSocket);
	
	sleep(1);
	
	ostringstream out;
	out << "http://localhost:" << port;
	Http client(out.str());
	
	ostringstream out2;
	debug("putting to %s",out.str().c_str());
	client.put(NULL,&out2);
	debug("done putting to %s",out.str().c_str());
	ASSERT_EQ(TEST1_MSG,out2.str());
}