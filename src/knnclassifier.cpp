#include "knnclassifier.hpp"
#include "dataparser.hpp"

#include <vector>

void KnnClassifier::_initializeTypeToDistanceMap() {
	TYPE_TO_DISTANCE_FUNCTION[EUCLIDEAN] = new EuclideanDistanceMetric();
}

KnnClassifier::KnnClassifier(int k, const Data& dataset, const DistanceMetricType& distanceMetricType): _k(k), _dataset(dataset)
{
	_initializeTypeToDistanceMap();
	_distanceMetric = TYPE_TO_DISTANCE_FUNCTION[distanceMetricType];
}

int KnnClassifier::classify(const std::vector<int>& sample) {
	// TODO: KNN algorithm should help here.
}
