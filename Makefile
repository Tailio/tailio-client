a.out : main.cpp
	g++ main.cpp -lcurl -I/System/Library/Frameworks/ApplicationServices.framework/Frameworks/HIServices.framework/Headers -framework ApplicationServices