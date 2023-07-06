#include <gtest/gtest.h>
#include <vector>
#include "../src/headers/Tape.h"

const std::string filepath = "./file.txt";

TEST(writeFileToVector, dataWasWrittenCorrect) {
	vector<int> actual = {1,2,3,4,5};
	vector<int> real = writeDataToVector(filepath);
	ASSERT_EQ(actual, real);
}

TEST(writeDataToVector, dataWasWrittenIncorrect) {
	vector<int> actual = {5,4,3,2,1};
	vector<int> real = writeDataToVector(filepath);
	ASSERT_NE(actual, real);
}

TEST(writeDataToFile, dataWasWrittenCorrect) {
	vector<int> actual = {1,2,3,4,5,6};
	writeVectorToFile(actual, filepath);
	vector<int> real = writeDataToVector(filepath);
	EXPECT_EQ(real, actual);
	writeVectorToFile(vector<int>{1,2,3,4,5}, filepath);
}

struct TapeTest : public testing::Test {
	Tape *tape;
	void SetUp() {tape = new Tape();}
	void TearDown() {delete tape;}
};

TEST_F(TapeTest, checkForEmptyTapeTest) {
	vector<int> actualTape;
	ASSERT_EQ(actualTape, tape->getTape());
}

TEST_F(TapeTest, doNotConsistPathsTest) {
	ASSERT_TRUE(!tape->consistPaths());
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
