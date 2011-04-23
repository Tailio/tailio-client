
#include <cstdlib>
#include <fstream>
#include <iostream>



#include "clipboard.hpp"

using namespace std;

namespace tailio {
	
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
}