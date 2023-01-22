#include "knnclassifier.hpp"
#include "dataparser.hpp"

#include <vector>
#include <algorithm>

void KnnClassifier::_initializeTypeToDistanceMap() {
	TYPE_TO_DISTANCE_FUNCTION[EUCLIDEAN] = new EuclideanDistanceMetric();
}

KnnClassifier::KnnClassifier(int k, const Data& dataset, const DistanceMetricType& distanceMetricType): _k(k), _dataset(dataset)
{
	_initializeTypeToDistanceMap();
	_distanceMetric = TYPE_TO_DISTANCE_FUNCTION[distanceMetricType];
}

int KnnClassifier::classify(const Data& sample) {
	std::vector<int> heap;
	// TODO: KNN algorithm should help here.
	// Loop through all datapoints to find knn.
		// Get the data at that point
		// Get distance between that sample and this one
	const std::vector<int>& dimensions = _dataset.getDimensions();

	for(int sampleIndex; sampleIndex < dimensions.front(); ++sampleIndex)	{
		Data currSample = _dataset.getSample(sampleIndex);
		const double distance = _distanceMetric->distance(sample, currSample);
}
	return 0;
}
