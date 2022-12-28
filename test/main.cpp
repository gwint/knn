#include "../src/dataparser.hpp"

#include <gtest/gtest.h>

TEST(data, testDataReadFromFile_getDimensions) {
	Data data = Data::retrieveFromFile("testdatafile.txt");
	std::vector<int> dimensions = data.getDimensions();
   	EXPECT_EQ(dimensions.size(), 0);	
}

TEST(data, testDataReadFromFile_getValue) {
	Data data = Data::retrieveFromFile("testdatafile.txt");
	int value = data.getValue(0, 0);
	EXPECT_EQ(value, 0);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

