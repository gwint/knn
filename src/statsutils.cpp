#include "statsutils.hpp"
#include "dataparser.hpp"

#include <assert.h>
#include <stdlib.h>
#include <unordered_set>

const int POSITIVE_LABEL_INDEX = 0;
const int NEGATIVE_LABEL_INDEX = 1;

std::vector<Data> StatsUtils::getSplitData(const Data& data, const Data& classifications, double testProportion) {
	std::vector<Data> splitData;
	assert(data.getNumSamples() == classifications.getNumSamples());

	const int numSamplesTotal = data.getNumSamples();
	const int numSamplesInTestGroup = testProportion * numSamplesTotal;

	std::srand(1);
	std::unordered_set<int> randomIndicesForTestGroup;
	while(randomIndicesForTestGroup.size() < numSamplesInTestGroup) {
		randomIndicesForTestGroup.insert(rand() % numSamplesTotal);	
	}

	Data trainingData;
	Data trainingClassifications;
	Data testData;
	Data testClassifications;

	for(int i = 0; i < numSamplesTotal; ++i) {
		if(randomIndicesForTestGroup.find(i) != randomIndicesForTestGroup.end()) {
			const Data sample = data.getSample(i);
			testData.addSample(sample);
			testClassifications.addSample(classifications.getSample(i));
		}
		else {
			trainingData.addSample(data.getSample(i));
			trainingClassifications.addSample(classifications.getSample(i));
		}
	}

	testData.getDimensions().insert(testData.getDimensions().begin(), data.getDimensionsImmutable().begin(), data.getDimensionsImmutable().end());
	testData.getDimensions()[0] = numSamplesInTestGroup;
	testClassifications.getDimensions().push_back(numSamplesInTestGroup);
	testClassifications.getDimensions().push_back(1);

	trainingData.getDimensions().insert(trainingData.getDimensions().begin(), data.getDimensionsImmutable().begin(), data.getDimensionsImmutable().end());
	trainingData.getDimensions()[0] = data.getNumSamples() - numSamplesInTestGroup;
	
	trainingClassifications.getDimensions().insert(trainingClassifications.getDimensions().begin(), classifications.getDimensionsImmutable().begin(), classifications.getDimensionsImmutable().end());
	trainingClassifications.getDimensions()[0] = data.getNumSamples() - numSamplesInTestGroup;

	return std::vector<Data>{trainingData, trainingClassifications, testData, testClassifications};
}

std::vector<std::vector<double>> StatsUtils::getConfusionMatrix(const Data& testClassifications, const Data& actualClassifications, const std::vector<int>& labels) {
	assert(testClassifications.getNumSamples() == actualClassifications.getNumSamples());
	assert(testClassifications.getInputVectorsImmutable().size() == actualClassifications.getInputVectorsImmutable().size());

	double truePositiveProportion = _getTruePositiveProportion(actualClassifications, testClassifications, labels);

	double falsePositiveProportion = _getFalsePositiveProportion(actualClassifications, testClassifications, labels);

	double trueNegativeProportion = _getTrueNegativeProportion(actualClassifications, testClassifications, labels);

	double falseNegativeProportion = _getFalseNegativeProportion(actualClassifications, testClassifications, labels);
	
	return std::vector<std::vector<double>>{std::vector<double>{truePositiveProportion, falsePositiveProportion}, std::vector<double>{falseNegativeProportion, trueNegativeProportion}};
}

double StatsUtils::_getTrueNegativeProportion(const Data& actual, const Data& test, const std::vector<int>& labels) {
	int numBenignSamples = 0;
	int numBenignAndPredictedBenignSamples = 0;

	for(int sampleIndex = 0; sampleIndex < actual.getNumSamples(); ++sampleIndex) {
		int testClassification = test.getSample(sampleIndex).getValue(std::vector<int>{0});
		int actualClassification = actual.getSample(sampleIndex).getValue(std::vector<int>{0});

		if(testClassification == labels[NEGATIVE_LABEL_INDEX]) {
			++numBenignSamples;
			if(actualClassification == labels[NEGATIVE_LABEL_INDEX]) {
				++numBenignAndPredictedBenignSamples;
			}
		}
	}

	return numBenignSamples / numBenignAndPredictedBenignSamples;
}

double StatsUtils::_getFalseNegativeProportion(const Data& actual, const Data& test, const std::vector<int>& labels) {
	return 1 - _getTruePositiveProportion(actual, test, labels);
}

double StatsUtils::_getTruePositiveProportion(const Data& actual, const Data& test, const std::vector<int>& labels) {
	int numMalignantSamples = 0;
	int numMalignantAndPredictedMalignantSamples = 0;

	for(int sampleIndex = 0; sampleIndex < actual.getNumSamples(); ++sampleIndex) {
		int testClassification = test.getSample(sampleIndex).getValue(std::vector<int>{0});
		int actualClassification = actual.getSample(sampleIndex).getValue(std::vector<int>{0});

		if(testClassification == labels[POSITIVE_LABEL_INDEX]) {
			++numMalignantSamples;
			if(actualClassification == labels[POSITIVE_LABEL_INDEX]) {
				++numMalignantAndPredictedMalignantSamples;
			}
		}
	}

	return numMalignantSamples / numMalignantAndPredictedMalignantSamples;
}

double StatsUtils::_getFalsePositiveProportion(const Data& actual, const Data& test, const std::vector<int>& labels) {
	return 1 - _getTrueNegativeProportion(actual, test, labels);
}


