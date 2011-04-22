#include <cstdio>
#include <fstream>
#include <iostream>
#include <curl/curl.h>

#ifdef __APPLE__
#include <HIServices.h>
#endif

using namespace std;

size_t write_data( void *ptr, size_t size, size_t nmemb, void *userdata);
size_t read_data( void *ptr, size_t size, size_t nmemb, void *userdata);

class Clipboard {
public:
	Clipboard();
	virtual ~Clipboard();
	void copyTo(const void* buf, size_t size);
private:
	PasteboardRef theClipboard;
};

class Http {
public: 
	Http(const char* url);
	virtual ~Http();
	void put(const istream* in, const ostream* out);
private:
	void init(const istream* in, const ostream* out);

	CURL* curl;
};


int main(int argc, char** argv) {
	const char* url = "http://localhost:8000/abc";
	Clipboard cboard;
	cboard.copyTo(url, strlen(url));
	Http http(url);
	http.put(&cin,&cout);
	return 0;
}

size_t read_data( void *ptr, size_t size, size_t nmemb, void *userdata) {
	istream &in = *((istream*) userdata);
	char* buffer = (char*) ptr;
	in.get(buffer,size * nmemb);
	return in.gcount();
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


Clipboard::Clipboard() {
#ifdef __APPLE__
	PasteboardCreate( kPasteboardClipboard, &theClipboard );
#endif	
}

Clipboard::~Clipboard() {
}


void Clipboard::copyTo(const void* buf, size_t size) {
#ifdef __APPLE__
	OSStatus err = noErr;
	PasteboardClear( theClipboard );
	CFDataRef textData = CFDataCreate( kCFAllocatorDefault, // 6
	                                    (UInt8*) buf, size );
    err = PasteboardPutItemFlavor( theClipboard, (PasteboardItemID)1,// 7
                        CFSTR("public.utf8-plain-text"),
                        textData, 0 );
#endif
}
