#include "statsutils.hpp"
#include "dataparser.hpp"

#include <assert.h>
#include <stdlib.h>
#include <unordered_set>

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
