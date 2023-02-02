#include <iostream>
#include <vector>

#include "dataparser.hpp"
#include "knnclassifier.hpp"
#include "statsutils.hpp"

int main(int argc, char** argv) {
	Data data = Data::retrieveFromCSVFile("breast-cancer-wisconsin.data");
	Data classifications = Data::retrieveClassificationsFromCSVFile("breast-cancer-wisconsin-labels.csv");
	std::vector<Data> splitData = StatsUtils::getSplitData(data, classifications, 0.20);
	const Data& trainingData = splitData[0];
	const Data& trainingClassifications = splitData[1];
	const Data& testData = splitData[2];
	const Data& testClassifications = splitData[3];

	KnnClassifier classifier(25, trainingData, trainingClassifications);
	std::vector<int> classifierResults = classifier.classify(testData);

	// TODO: Compute confusion matrix
	for(int i = 0; i < classifierResults.size(); ++i) {
		std::cout << "result: " << classifierResults[i] << '\n';
	}

	return 0;
}
