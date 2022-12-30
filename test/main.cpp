#include "../src/dataparser.hpp"

#include <gtest/gtest.h>

TEST(data, testDataReadFromFile_getDimensions) {
	Data data = Data::retrieveFromFile("testdatafile.txt");
	std::vector<int> dimensions = data.getDimensions();
   	EXPECT_EQ(dimensions.size(), 2);	
}

TEST(data, testDataReadFromFile_getValue) {
	Data data = Data::retrieveFromFile("testdatafile.txt");
	EXPECT_EQ(data.getValue(std::vector<int>{0, 0}), 1);
	EXPECT_EQ(data.getValue(std::vector<int>{0, 1}), 2);
	EXPECT_EQ(data.getValue(std::vector<int>{0, 2}), 3);
	EXPECT_EQ(data.getValue(std::vector<int>{1, 0}), 4);
	EXPECT_EQ(data.getValue(std::vector<int>{1, 1}), 5);
	EXPECT_EQ(data.getValue(std::vector<int>{1, 2}), 6);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

