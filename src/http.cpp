
#include "http.hpp"
using namespace std;

namespace tailio {
	
	size_t read_data( void *ptr, size_t size, size_t nmemb, void *userdata) {
		istream &in = *((istream*) userdata);
		char* buffer = (char*) ptr;
		const size_t max = size * nmemb;
		size_t totalRead = 0;
		
		while (in.good() && totalRead < max) {
			size_t read = in.readsome(buffer,max - totalRead);
			if (!read) {
				if (totalRead || !in.good()) {
					break;
				} else {
					buffer[0] = in.get();
					read++;
				}
			}
			totalRead += read;
			buffer += read;
		}
		return totalRead;
	}


	size_t write_data( void *ptr, size_t size, size_t nmemb, void *userdata) {
		ostream &fout = *((ostream*) userdata);
		char* buffer = (char*) ptr;
		size_t result = size * nmemb;
		fout.write(buffer,result);
		return result;
	}


	Http::Http(const char* url) {
		curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_URL, url);
	}

	Http::~Http() {
		if (curl) { 
			curl_easy_cleanup(curl);
			curl = NULL;
		}
	}

	void Http::init(const istream* in, const ostream* out) {
		if (in) {
			curl_easy_setopt(curl,CURLOPT_READFUNCTION,read_data);
			curl_easy_setopt(curl,CURLOPT_READDATA,in);
		}
	
		if (out) {
			curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_data);
			curl_easy_setopt(curl,CURLOPT_WRITEDATA,out);
		}
	}

	void Http::put(const istream* istream, const ostream* ostream) {
		init(istream,ostream);
		curl_easy_setopt(curl,CURLOPT_PUT,1);
		curl_easy_perform(curl);
	}


}
