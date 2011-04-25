
#include <gtest/gtest.h>

#include "log.hpp"
#include "socket.hpp"
#include "thread.hpp"


using namespace std;
using namespace tailio;

const string SERVER_MSG_1 = "yo from server\n";

void* serverGo(void* arg) {
	ServerSocket& server = *((ServerSocket*) arg);
	Socket* pSocket = server.accept();
	while (pSocket) {
		string str = SERVER_MSG_1;
		pSocket->send(str.c_str(),str.length());
		server.close(pSocket);
		pSocket = server.accept();
	}
	return NULL;
}

TEST(SocketTest,Go) {
	int port = 31555;
	ServerSocket server(port);
	Thread thread(serverGo);
	thread.start(&server);
	
	sleep(1);
	
	Socket socket("127.0.0.1",port);
	
	int length = 100;
	char buffer[length];
	int bytesRead = socket.receive(buffer,length);
	buffer[bytesRead] = 0;
	debug("got %s",buffer);
	
	server.close();
	thread.join();
	
	string str = buffer;
	ASSERT_EQ(SERVER_MSG_1,str);
}
