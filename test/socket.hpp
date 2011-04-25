#ifndef _SOCKET_HPP_
#define _SOCKET_HPP_

#include <iostream>
#include <set>

using namespace std;

namespace tailio {

	typedef int SocketHandle;
	class ServerSocket;

	class Socket {
	public:
		Socket(const string& host, int port);
		virtual ~Socket();
		void send(const void* buffer, int count);
		int receive(void* buffer, int count);
		void close();
		friend class ServerSocket;
	private:
		SocketHandle handle;
		Socket(SocketHandle handle);
	};

	class ServerSocket {
	public:
		ServerSocket(int port);
		virtual ~ServerSocket();
		Socket* accept();
		void close();
		void close(Socket* socket);
	private:	
		SocketHandle handle;
		int port;
		
		typedef set<Socket*> SocketSet;
		SocketSet sockets;
	};


}

#endif