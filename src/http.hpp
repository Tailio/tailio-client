#ifndef _HTTP_HPP_
#define _HTTP_HPP_

#include <iostream>
#include <curl/curl.h>

using namespace std;

namespace tailio {
	class Http {
	public: 
		Http(const char* url);
		virtual ~Http();
		void put(const istream* in, const ostream* out);
	private:
		void init(const istream* in, const ostream* out);

		CURL* curl;
	};
}

#endif