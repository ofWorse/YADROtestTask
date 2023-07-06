#include "../src/Tape.h"
#include <gtest/gtest.h>
#include <vector>

TEST(Tape, testEmptyTape) {
	Tape tape;
	vector<int> actualTape;
	ASSERT_EQ(actualTape, tape.getTape());
}

TEST(Tape, testGivenDataFromFileToVector) {
	Tape tape;
	vector<int> actualTape = {1,2,3,4,5};
	
	ASSERT_EQ(, val2);

}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
