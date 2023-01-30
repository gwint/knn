#include "../src/dataparser.hpp"
#include "../src/distancemetric.hpp"
#include "../src/statsutils.hpp"

#include <gtest/gtest.h>
#include <math.h>
#include <iostream>
#include <unordered_set>

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

	EXPECT_EQ(data.getDimensions().size(), 2);
	EXPECT_EQ(data.getDimensions()[0], 2);
	EXPECT_EQ(data.getDimensions()[1], 3);

	Data sample1 = data.getSample(1);

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
	Data data = Data::retrieveFromCSVFile("./test/testdatafile10x10.csv");
	Data classifications = Data::retrieveClassificationsFromCSVFile("./test/testdatalabels10.txt");

	std::vector<Data> trainingTestSplitData = StatsUtils::getSplitData(data, classifications, 0.2);

	// Verify number of samples in training/test sets.
	const Data& trainingData = trainingTestSplitData[0];
	const Data& trainingClassifications = trainingTestSplitData[1];
	const Data& testData = trainingTestSplitData[2];
	const Data& testClassifications = trainingTestSplitData[3];

	// Check dimensions.
	EXPECT_EQ(trainingData.getDimensionsImmutable().size(), 2);
	EXPECT_EQ(trainingData.getDimensionsImmutable()[0], 8);
	EXPECT_EQ(trainingData.getDimensionsImmutable()[1], 10);

	EXPECT_EQ(trainingClassifications.getDimensionsImmutable().size(), 2);
	EXPECT_EQ(trainingClassifications.getDimensionsImmutable()[0], 8);
	EXPECT_EQ(trainingClassifications.getDimensionsImmutable()[1], 1);

	EXPECT_EQ(testData.getDimensionsImmutable().size(), 2);
	EXPECT_EQ(testData.getDimensionsImmutable()[0], 2);
	EXPECT_EQ(testData.getDimensionsImmutable()[1], 10);

	EXPECT_EQ(testClassifications.getDimensionsImmutable().size(), 2);
	EXPECT_EQ(testClassifications.getDimensionsImmutable()[0], 2);
	EXPECT_EQ(testClassifications.getDimensionsImmutable()[1], 1);

	EXPECT_EQ(trainingData.getInputVectorsImmutable().size(), 80);
	EXPECT_EQ(trainingClassifications.getInputVectorsImmutable().size(), 8);
	EXPECT_EQ(testData.getInputVectorsImmutable().size(), 20);
	EXPECT_EQ(testClassifications.getInputVectorsImmutable().size(), 2);

	// Check that data in training and test sets data map back to
	// samples from the original data set.
	const int totalNumSamples = data.getNumSamples();
	const int numTrainingSamples = totalNumSamples - (totalNumSamples * 0.2);
	int numMatchesFound = 0;
	std::unordered_set<int> matchedIndices;
	for(int trainingSampleIndex = 0; trainingSampleIndex < trainingData.getNumSamples(); ++trainingSampleIndex) {
		bool matchFound = false;
		const Data& trainingSample = trainingData.getSample(trainingSampleIndex);

		for(int possMatchSampleIndex = 0; possMatchSampleIndex < data.getNumSamples(); ++possMatchSampleIndex) {
			const Data& possMatchSample = data.getSample(possMatchSampleIndex);
			if(trainingSample == possMatchSample && 
				matchedIndices.find(possMatchSampleIndex) == matchedIndices.end()) {
				matchedIndices.insert(possMatchSampleIndex);
				matchFound = true;
				break;
			}
		}

		if(matchFound) {
			++numMatchesFound;
		}
	}

	EXPECT_EQ(numMatchesFound, trainingData.getNumSamples());

	numMatchesFound = 0;
	matchedIndices.clear();
	for(int testSampleIndex = 0; testSampleIndex < testData.getNumSamples(); ++testSampleIndex) {
		bool matchFound = false;
		const Data& testSample = testData.getSample(testSampleIndex);

		for(int possMatchSampleIndex = 0; possMatchSampleIndex < data.getNumSamples(); ++possMatchSampleIndex) {
			const Data& possMatchSample = data.getSample(possMatchSampleIndex);
			if(testSample == possMatchSample && 
				matchedIndices.find(possMatchSampleIndex) == matchedIndices.end()) {
				matchedIndices.insert(possMatchSampleIndex);
				matchFound = true;
				break;
			}
		}

		if(matchFound) {
			++numMatchesFound;
		}
	}

	EXPECT_EQ(numMatchesFound, testData.getNumSamples());
}

TEST(data, testData_testAddSample) {
	Data data = Data::retrieveClassificationsFromCSVFile("./test/testdatalabels.txt");
	EXPECT_EQ(data.getDimensions().size(), 2);
	EXPECT_EQ(data.getDimensions()[0], 2);
	EXPECT_EQ(data.getDimensions()[1], 1);
	EXPECT_EQ(data.getValue(std::vector<int>{0}), 0);
	EXPECT_EQ(data.getValue(std::vector<int>{1}), 1);

	Data dataCopy = Data(data);

	Data sample = dataCopy.getSample(0);

	EXPECT_EQ(sample.getDimensions().size(), 2);
	EXPECT_EQ(sample.getDimensions()[0], 1);
	EXPECT_EQ(sample.getDimensions()[1], 1);
	EXPECT_EQ(sample.getValue(std::vector<int>{0, 0}), 0);

	data.addSample(sample);

	EXPECT_EQ(data.getValue(std::vector<int>{0, 0}), 0);
	EXPECT_EQ(data.getValue(std::vector<int>{1, 0}), 1);
	EXPECT_EQ(data.getValue(std::vector<int>{2, 0}), 0);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

