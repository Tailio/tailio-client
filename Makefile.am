AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

bin_PROGRAMS = tailio
tailio_SOURCES =  src/main.cpp src/http.hpp src/http.cpp \
                src/clipboard.hpp src/clipboard.cpp

tailio_CPPFLAGS = -I/System/Library/Frameworks/ApplicationServices.framework/Frameworks/HIServices.framework/Headers
tailio_LDFLAGS = -lcurl -framework ApplicationServices

dist_noinst_SCRIPTS = autogen.sh
