#include "../src/dataparser.hpp"
#include "../src/distancemetric.hpp"

#include <gtest/gtest.h>
#include <math.h>
#include <iostream>

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

	// TODO: verify contents of dimensions here to make sure
	// it's correct
	EXPECT_EQ(data.getDimensions().size(), 2);
	EXPECT_EQ(data.getDimensions()[0], 2);
	EXPECT_EQ(data.getDimensions()[1], 3);

	Data sample1 = data.getSample(1);

	std::cout << "data dimensions: ";
	for(int i = 0; i < sample1.getDimensions().size(); ++i) {
		std::cout << " " << sample1.getDimensions()[i];
	}
	std::cout << '\n';

	EXPECT_EQ(sample1.getDimensions().size(), 2);
	EXPECT_EQ(sample1.getDimensions()[0], 1);
	EXPECT_EQ(sample1.getDimensions()[1], 3);
	
	EXPECT_EQ(sample1.getValue(std::vector<int>{0, 0}), 4);
	EXPECT_EQ(sample1.getValue(std::vector<int>{0, 1}), 5);
	EXPECT_EQ(sample1.getValue(std::vector<int>{0, 2}), 6);

	Data sample2 = data.getSample(0);
	
	EXPECT_EQ(sample2.getValue(std::vector<int>{0, 0}), 1);
	EXPECT_EQ(sample2.getValue(std::vector<int>{0, 1}), 2);
	EXPECT_EQ(sample2.getValue(std::vector<int>{0, 2}), 3);
}

TEST(data, testEuclideanDistance_2d_sample_distance) {
	Data data = Data::retrieveFromCSVFile("./test/testdatafile.txt");
	Data sample1 = data.getSample(0);
	Data sample2 = data.getSample(1);

	DistanceMetric* euclideanDist = new EuclideanDistanceMetric();
	EXPECT_EQ(euclideanDist->distance(sample1, sample2), sqrt(27));
}

TEST(data, testData_testReadClassificationsFile) {
	Data data = Data::retrieveClassificationsFromCSVFile("./test/testdatalabels.txt");
	EXPECT_EQ(data.getDimensions().size(), 2);
	EXPECT_EQ(data.getDimensions()[0], 2);
	EXPECT_EQ(data.getDimensions()[1], 1);
	EXPECT_EQ(data.getValue(std::vector<int>{0, 0}), 0);
	EXPECT_EQ(data.getValue(std::vector<int>{1, 0}), 1);
}

TEST(data, testClassifier_classify) {
	Data data = Data::retrieveFromCSVFile("./test/testdatafile.txt");
	Data classifications = Data::retrieveClassificationsFromCSVFile("./test/testdatalabels.txt");

	EXPECT_EQ(true, false);
}

TEST(statsutils, testGetSplitData) {
	Data data = Data::retrieveFromCSVFile("./test/testdatafile.txt");
	Data classifications = Data::retrieveClassificationsFromCSVFile("./test/testdatalabels.txt");

	std::vector<Data> trainingTestSplitData = StatsUtils::getSplitData(data, classifications, 0.15);

	EXPECT_EQ(true, false);
}

TEST(data, testData_testAddSample) {
	Data data = Data::retrieveClassificationsFromCSVFile("./test/testdatalabels.txt");
	EXPECT_EQ(data.getDimensions().size(), 2);
	EXPECT_EQ(data.getDimensions()[0], 2);
	EXPECT_EQ(data.getDimensions()[1], 1);
	EXPECT_EQ(data.getValue(std::vector<int>{0}), 0);
	EXPECT_EQ(data.getValue(std::vector<int>{1}), 1);

	Data dataCopy = Data(data);
	std::cout << "got here" << '\n';

	Data sample = dataCopy.getSample(0);

	std::cout << "got here" << '\n';

	EXPECT_EQ(sample.getDimensions().size(), 2);
	EXPECT_EQ(sample.getDimensions()[0], 1);
	EXPECT_EQ(sample.getDimensions()[1], 1);
	EXPECT_EQ(sample.getValue(std::vector<int>{0, 0}), 0);

	std::cout << "got here" << '\n';

	data.addSample(sample);

	std::cout << "got here" << '\n';

	EXPECT_EQ(data.getValue(std::vector<int>{0, 0}), 0);
	EXPECT_EQ(data.getValue(std::vector<int>{1, 0}), 1);
	EXPECT_EQ(data.getValue(std::vector<int>{2, 0}), 0);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

