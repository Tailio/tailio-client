#ifndef _HTTP_HPP_
#define _HTTP_HPP_

#include <iostream>
#include <curl/curl.h>

#include "mutex.hpp"

using namespace std;

namespace tailio {
	class Http {
	public: 
		Http(const string& url, int bufferSize = 2048);
		virtual ~Http();
		void put(istream* in, ostream* out);
	private:
		void init(istream* in, ostream* out);
		CURL* curl;
	};
}

#endif