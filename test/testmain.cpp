
#include <iostream>
#include <gtest/gtest.h>

using namespace std;

TEST(BlahTest,FooTest) {
	cout << "yo" << endl;
	EXPECT_TRUE(false);
	EXPECT_TRUE(true);	
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
