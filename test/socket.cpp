
#include <errno.h>

#include <arpa/inet.h>
#include <sys/socket.h>


#include "log.hpp"
#include "socket.hpp"


using namespace std;
using namespace tailio;


ServerSocket::ServerSocket(int port) {
	handle = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	debug("created socket %d",handle);
	
	int optval = 1;
	setsockopt(handle,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));

	sockaddr_in address;
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(port);
	
	int result = bind(handle, (sockaddr *) &address, sizeof(address));
	if (result < 0) {
		debug("Bind to address %s:%d failed: %d",inet_ntoa(address.sin_addr),port,result);
		throw result;
	}
	debug("server socket bound");
	
	result = listen(handle, -1);
	if (result < 0) {
		debug("Listen to address %s failed: %d", inet_ntoa(address.sin_addr), result);
		throw result;
	}
	debug("server socket listening");
}

ServerSocket::~ServerSocket() {
	for (SocketSet::iterator it = sockets.begin(); it != sockets.end(); it++) {
		delete *it;
	}
	
	if (handle) {
		close();
	}
}



Socket* ServerSocket::accept() {
	Socket* result = NULL;
	if (handle) {
		sockaddr_in address;
		unsigned int sizeOfAddress = sizeof(address);
		debug("accepting socket %d",handle);
		int clientHandle = ::accept(handle,(sockaddr*) &address,&sizeOfAddress);
		if (clientHandle >= 0) {
			debug("Accepted : %d",clientHandle);
			result = new Socket(clientHandle);
			sockets.insert(result);
		} else {
			debug("Accept failed: %d %s",errno,strerror(errno));
		}
	}	
	return result;
}


void ServerSocket::close() {
	if (handle) {
		debug("closing server socket");
		::close(handle);
		handle = NULL;
	}
}

void ServerSocket::close(Socket* socket) {
	if (socket) {
		debug("closing client socket %d", socket->handle);
		for (SocketSet::iterator it = sockets.begin(); it != sockets.end(); it++) {
			if (*it == socket) {
				sockets.erase(it);
				break;
			}
		}
		socket->close();
		delete socket;
	}
}

Socket::Socket(const string& host, int port) {
	handle = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	sockaddr_in address;
	memset(&address, 0, sizeof(address));     /* Zero out structure */
    address.sin_family      = AF_INET;             /* Internet address family */
    address.sin_addr.s_addr = inet_addr(host.c_str());   /* Server IP address */
    address.sin_port        = htons(port);

	int res = ::connect(handle, (sockaddr *) &address, sizeof(address));
	if (res < 0) {
		debug("connect failed with result %d",res);
		throw res;
	}
	debug("socket connected");
}

Socket::Socket(SocketHandle zHandle) : handle(zHandle) {
	
}

void Socket::close() {
	if (handle) {
		debug("closing socket");
		::close(handle);
		handle = NULL;
	}
}

Socket::~Socket() {
	if (handle) {
		close();
	}
}

void Socket::send(const void* buffer, int bufferLength) {
	int totalSent = 0;
	int toSend = bufferLength;
	char* ptr = (char*) buffer;
	while (totalSent < bufferLength) {
		int sent = ::send(handle,ptr,toSend, 0);
		totalSent += sent;
		ptr += sent;
		toSend = (totalSent - sent);
	}
}

int Socket::receive(void* buffer, int max) {
	return ::recv(handle,(char*) buffer, max, 0);
}
