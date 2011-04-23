CC=g++
CFLAGS=-I. -I/System/Library/Frameworks/ApplicationServices.framework/Frameworks/HIServices.framework/Headers
SRCDIR=src
DEPS = $(SRCDIR)/http.hpp $(SRCDIR)/clipboard.hpp
OBJ = main.o http.o clipboard.o
LIBS = -lcurl -framework ApplicationServices

%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tailio: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


clean:
	rm $(OBJ) tailio