#include "../src/dataparser.hpp"
#include "../src/distancemetric.hpp"

#include <gtest/gtest.h>
#include <math.h>

TEST(data, testDataReadFromFile_getDimensions) {
	Data data = Data::retrieveFromCSVFile("./test/testdatafile.txt");
	std::vector<int> dimensions = data.getDimensions();
   	EXPECT_EQ(dimensions.size(), 2);	
}

TEST(data, testDataReadFromFile_getValue) {
	Data data = Data::retrieveFromCSVFile("./test/testdatafile.txt");
	EXPECT_EQ(data.getValue(std::vector<int>{0, 0}), 1);
	EXPECT_EQ(data.getValue(std::vector<int>{0, 1}), 2);
	EXPECT_EQ(data.getValue(std::vector<int>{0, 2}), 3);
	EXPECT_EQ(data.getValue(std::vector<int>{1, 0}), 4);
	EXPECT_EQ(data.getValue(std::vector<int>{1, 1}), 5);
	EXPECT_EQ(data.getValue(std::vector<int>{1, 2}), 6);
}

TEST(data, testEuclideanDistance_2d_distance) {
	Data data = Data::retrieveFromCSVFile("./test/testdatafile.txt");

	DistanceMetric* euclideanDist = new EuclideanDistanceMetric();
	std::vector<int> sample1{0, 0};
	std::vector<int> sample2{0, 1};
	EXPECT_EQ(euclideanDist->distance(sample1, sample2), 1);
}

TEST(data, testEuclideanDistance_3d_distance) {
	Data data = Data::retrieveFromCSVFile("./test/testdatafile.txt");

	DistanceMetric* euclideanDist = new EuclideanDistanceMetric();
	std::vector<int> sample1{0, 0, 0};
	std::vector<int> sample2{3, 3, 3};
	EXPECT_EQ(euclideanDist->distance(sample1, sample2), sqrt(27));
}

TEST(data, testData_getSample) {
	Data data = Data::retrieveFromCSVFile("./test/testdatafile.txt");
	Data sample1 = data.getSample(1);
	
	EXPECT_EQ(sample1.getValue(std::vector<int>{0}), 4);
	EXPECT_EQ(sample1.getValue(std::vector<int>{1}), 5);
	EXPECT_EQ(sample1.getValue(std::vector<int>{2}), 6);

	Data sample2 = data.getSample(0);
	
	EXPECT_EQ(sample2.getValue(std::vector<int>{0}), 1);
	EXPECT_EQ(sample2.getValue(std::vector<int>{1}), 2);
	EXPECT_EQ(sample2.getValue(std::vector<int>{2}), 3);
}

TEST(data, testEuclideanDistance_2d_sample_distance) {
	Data data = Data::retrieveFromCSVFile("./test/testdatafile.txt");
	Data sample1 = data.getSample(0);
	Data sample2 = data.getSample(1);

	DistanceMetric* euclideanDist = new EuclideanDistanceMetric();
	EXPECT_EQ(euclideanDist->distance(sample1, sample2), sqrt(27));
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

