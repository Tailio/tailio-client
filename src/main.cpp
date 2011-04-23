
#include "http.hpp"
#include "clipboard.hpp"

using namespace tailio;

int main(int argc, char** argv) {
	const char* url = "http://localhost:8000/abc";
	Clipboard cboard;
	cboard.copyTo(url, strlen(url));
	Http http(url);
	http.put(&cin,&cout);
	return 0;
}

