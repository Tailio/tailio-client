
AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}



bin_PROGRAMS = tailio
check_PROGRAMS = tailio_test

SOURCES = src/http.hpp src/http.cpp \
                src/clipboard.hpp src/clipboard.cpp \
				src/mutex.hpp src/mutex.cpp \
				src/thread.hpp src/thread.cpp \
				src/log.hpp

tailio_SOURCES =  $(SOURCES) src/main.cpp 


tailio_test_SOURCES = $(SOURCES) test/testmain.cpp test/socket.hpp test/socket.cpp \
 							gtest-1.6.0/src/gtest-all.cc

if DEBUG
DEBUG_FLAGS = -g3 -O0 -D_DEBUG_
else
DEBUG_FLAGS = -O3
endif

MYCPPFLAGS = $(DEBUG_FLAGS) -Isrc -I/System/Library/Frameworks/ApplicationServices.framework/Frameworks/HIServices.framework/Headers -pthread
MYLDFLAGS = -lcurl -framework ApplicationServices -pthread

tailio_CPPFLAGS = $(MYCPPFLAGS)
tailio_LDFLAGS = $(MYLDFLAGS)

tailio_test_CPPFLAGS = $(MYCPPFLAGS) -Igtest-1.6.0 -Igtest-1.6.0/include
tailio_test_LDFLAGS = $(MYLDFLAGS)

dist_noinst_SCRIPTS = autogen.sh

TESTS = tailio_test