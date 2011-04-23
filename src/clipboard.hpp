#ifndef _CLIPBOARD_HPP_
#define _CLIPBOARD_HPP_

#ifdef __APPLE__
#include <HIServices.h>
#endif

namespace tailio {
	class Clipboard {
	public:
		Clipboard();
		virtual ~Clipboard();
		void copyTo(const void* buf, size_t size);
	private:
		PasteboardRef theClipboard;
	};
}

#endif