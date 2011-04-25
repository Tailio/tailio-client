
#include <unistd.h>

#include "clipboard.hpp"
#include "http.hpp"
#include "thread.hpp"

using namespace tailio;

const char DEFAULT_BASE[] = "http://localhost:8000/";
const char DEFAULT_STREAM[] = "abc";
const char OPTIONS[] = "b:s:";

const char ARG_BASE = 'b';
const char ARG_STREAM = 's';

int main(int argc, char** argv) {
	string options = OPTIONS;
	string base = DEFAULT_BASE;
	string stream = DEFAULT_STREAM;
	
	int opt = getopt(argc,argv,options.c_str());
	while (opt != -1) {
		switch (opt) {
		case ARG_BASE:
			base = optarg;
			break;
		case ARG_STREAM:
			stream = optarg;
			break;
		}
		opt = getopt(argc,argv,options.c_str());
	}
	
	string url = base + stream;
	
	Clipboard cboard;
	cboard.copyTo(url.c_str(), url.length());
	
	Http http(url);
	http.put(&cin,&cout);
	
	return 0;
}


