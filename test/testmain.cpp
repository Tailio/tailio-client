
#include <iostream>
#include <gtest/gtest.h>

using namespace std;

#include "http-test.cpp"
#include "socket-test.cpp"
#include "thread-test.cpp"

int main(int argc, char** argv) {
#ifdef _DEBUG_
	cerr << "debug imo" << endl;
#endif
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
