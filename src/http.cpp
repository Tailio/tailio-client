
#include "http.hpp"
#include "log.hpp"

using namespace std;

namespace tailio {
	
	size_t read_data( void *ptr, size_t size, size_t nmemb, void *userdata) {
		istream &in = *((istream*) userdata);
		char* buffer = (char*) ptr;
		const size_t max = size * nmemb;
		size_t totalRead = 0;
		in.getline(buffer,max);
		int read = strlen(buffer);
		debug("Read %d bytes", read);
		buffer[read] = '\n';
		return read + 1;
	}


	size_t write_data( void *ptr, size_t size, size_t nmemb, void *userdata) {
		ostream &fout = *((ostream*) userdata);
		char* buffer = (char*) ptr;
		size_t result = size * nmemb;
		fout.write(buffer,result);
		return result;
	}


	Http::Http(const string& url, int bufferSize) {
		curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	}

	Http::~Http() {
		if (curl) { 
			curl_easy_cleanup(curl);
			curl = NULL;
		}
	}

	void Http::init(istream* in, ostream* out) {
		if (in) {
			curl_easy_setopt(curl,CURLOPT_READFUNCTION,read_data);
			curl_easy_setopt(curl,CURLOPT_READDATA,in);
		}
	
		if (out) {
			curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_data);
			curl_easy_setopt(curl,CURLOPT_WRITEDATA,out);
		}
	}

	void Http::put(istream* istream, ostream* ostream) {
		init(istream,ostream);
		curl_easy_setopt(curl,CURLOPT_PUT,1);
		curl_easy_perform(curl);
	}
}
